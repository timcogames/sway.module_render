#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <google/plugfixture.hpp>

using namespace sway;

class GeometryTestFixture : public PlugTestFixture {};

TEST_F(GeometryTestFixture, create_buffer) {
  auto *shaderStub = createShaderStub(globalGapiPlug);
  auto *shaderProgStub = createShaderProgStub(globalGapiPlug, shaderStub);

  gapi::ShaderCreateInfoSet infoSet;
  infoSet.vs.type = gapi::ShaderType::VERT;
  infoSet.vs.code = "";
  infoSet.fs.type = gapi::ShaderType::FRAG;
  infoSet.fs.code = "";
  auto *effect = new render::Effect(globalGapiPlug, infoSet);

  auto *idGeneratorStub = new render::global::IdGeneratorStub();
  ON_CALL(*idGeneratorStub, newGuid()).WillByDefault(testing::Return(1));

  auto *vertexArrayStub = new render::global::VertexArrayStub();
  ON_CALL(*vertexArrayStub, bind()).WillByDefault([&] {});
  ON_CALL(*vertexArrayStub, unbind()).WillByDefault([&] {});

  auto *bufferStub = new render::global::BufferStub();
  EXPECT_CALL(*bufferStub, mapRange(testing::_, testing::_, testing::_))
      .WillRepeatedly(testing::WithArg<1>(testing::Invoke([](u32_t size) {
        auto *data = malloc(size);
        return data;
      })));

  EXPECT_CALL(*bufferStub, unmap()).WillRepeatedly([] {
    // free(data);
  });

  auto *vertexAttribLayoutStub = new render::global::VertexAttribLayoutStub();
  EXPECT_CALL(*vertexAttribLayoutStub, addAttribute(testing::_)).Times(testing::Exactly(6 /* кол.-во вызовов */));

  EXPECT_CALL(*globalGapiPlug, createIdGenerator()).WillRepeatedly(testing::Return(idGeneratorStub));
  EXPECT_CALL(*globalGapiPlug, createVertexArray()).WillRepeatedly(testing::Return(vertexArrayStub));
  EXPECT_CALL(*globalGapiPlug, createBuffer(testing::_, testing::_)).WillRepeatedly(testing::Return(bufferStub));
  EXPECT_CALL(*globalGapiPlug, createVertexAttribLayout(shaderProgStub))
      .WillRepeatedly(testing::Return(vertexAttribLayoutStub));

  constexpr auto numInstances = 1;

  auto *geomDataDivisor =
      new render::GeomInstanceDataDivisor<render::procedurals::prims::Quadrilateral<math::VertexColor>>(
          {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL}, numInstances);

  auto *geomBuilder = new render::GeomBuilder(globalGapiPlug, idGeneratorStub);
  geomBuilder->reserve(1);
  geomBuilder->reserve(render::Constants::MAX_BUFFER_OBJECTS + 10 /* Выходим за рамки допустимого */);

  auto geometries = geomBuilder->getGeometries();
  ASSERT_EQ(geometries.size(), render::Constants::MAX_BUFFER_OBJECTS);

  render::GeometryCreateInfo geomCreateInfo;
  geomCreateInfo.indexed = true;
  geomCreateInfo.topology = gapi::TopologyType::TRIANGLE_LIST;
  geomCreateInfo.bo[render::Constants::IDX_VBO].desc.usage = gapi::BufferUsage::DYNAMIC;
  geomCreateInfo.bo[render::Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexColor);
  geomCreateInfo.bo[render::Constants::IDX_VBO].desc.capacity =
      4 * geomDataDivisor->getInstSize();  // rectGeomShape_->data()->getVtxSize();
  geomCreateInfo.bo[render::Constants::IDX_VBO].data = nullptr;

  geomCreateInfo.bo[render::Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
  geomCreateInfo.bo[render::Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
  auto idxs = geomDataDivisor->getIndices<numInstances>();
  geomCreateInfo.bo[render::Constants::IDX_EBO].desc.capacity = idxs.size();
  geomCreateInfo.bo[render::Constants::IDX_EBO].data = idxs.data();

  auto uid_0 = geomBuilder->createInstance<render::procedurals::prims::Quadrilateral<math::VertexColor>>(
      0, geomDataDivisor, geomCreateInfo, effect);

  auto *geomInstance_0 =
      static_cast<render::GeomInstance<render::procedurals::prims::Quadrilateral<math::VertexColor>> *>(
          geomBuilder->getGeometry(0));
  EXPECT_TRUE(geomInstance_0->getBuffer(render::Constants::IDX_VBO).has_value());
  EXPECT_TRUE(geomInstance_0->getBuffer(render::Constants::IDX_EBO).has_value());

  auto uid_1 = geomBuilder->createInstance<render::procedurals::prims::Quadrilateral<math::VertexColor>>(
      1, geomDataDivisor, geomCreateInfo, effect);

  auto *geomInstance_1 =
      static_cast<render::GeomInstance<render::procedurals::prims::Quadrilateral<math::VertexColor>> *>(
          geomBuilder->getGeometry(1));
  EXPECT_TRUE(geomInstance_1->getBuffer(render::Constants::IDX_VBO).has_value());
  EXPECT_TRUE(geomInstance_1->getBuffer(render::Constants::IDX_EBO).has_value());

  auto uid_2 = geomBuilder->create<render::procedurals::prims::Quadrilateral<math::VertexColor>>(
      2, render::GeometryCreateInfo(), geomDataDivisor->getVertexAttribs(), effect);

  // geomBuilder->getGeometry(2)->create(render::GeometryCreateInfo(), effect, geomDataDivisor->getVertexAttribs());
  EXPECT_TRUE(geomBuilder->getGeometry(2)->getBuffer(render::Constants::IDX_VBO).has_value());
  EXPECT_FALSE(geomBuilder->getGeometry(2)->getBuffer(render::Constants::IDX_EBO).has_value());

  geomInstance_0->remap();
  geomInstance_1->remap();

  // ---------------------
  shaderProgStub->use();
  shaderProgStub->unuse();
  // ---------------------

  // SAFE_DELETE_OBJECT(geomDataDivisor);
  SAFE_DELETE_OBJECT(vertexArrayStub);
  SAFE_DELETE_OBJECT(vertexAttribLayoutStub);
  SAFE_DELETE_OBJECT(bufferStub);
  SAFE_DELETE_OBJECT(idGeneratorStub);
  // SAFE_DELETE_OBJECT(geomBuilder);
  SAFE_DELETE_OBJECT(shaderStub);
  SAFE_DELETE_OBJECT(shaderProgStub);
  // SAFE_DELETE_OBJECT(effect);
}
