#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace sway;

TEST(Geom, createVertexData) {
  auto numVerts = 4;
  auto geomVertexData = std::make_shared<render::GeomVertexData<math::VertexColor>>(numVerts);

  auto pos = geomVertexData->template createAttrib<math::vec3f_t>(gapi::VertexSemantic::POS);
  ASSERT_FALSE(pos->enabled());

  pos->setData(0, math::vec3f_t(1.0F, 1.0F, 1.0F).data());
  pos->setData(1, math::vec3f_t(1.1F, 1.1F, 1.1F).data());
  pos->setData(2, math::vec3f_t(1.2F, 1.2F, 1.2F).data());
  pos->setData(3, math::vec3f_t(1.3F, 1.3F, 1.3F).data());

  auto col = geomVertexData->template createAttrib<math::vec4f_t>(gapi::VertexSemantic::COL);
  ASSERT_FALSE(col->enabled());

  col->setData(0, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).data());
  col->setData(1, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).data());
  col->setData(2, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).data());
  col->setData(3, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).data());

  geomVertexData->useSemanticSet({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  ASSERT_TRUE(pos->enabled());
  ASSERT_TRUE(col->enabled());

  // auto data = (math::VertexColor *)geomVertexData->getVertices();
  // for (auto i = 0; i < numVerts; i++) {
  //   std::cout << data[i] << std::endl;
  // }

  // free(data);
}

render::global::GapiPluginFunctionSet *globalGapiPlug;

class GeomTestFixture : public testing::Test {
protected:
  render::global::MockPluginFunctionSet mockedGapiPlug;

  void SetUp() { globalGapiPlug = &mockedGapiPlug; }

  void TearDown() { globalGapiPlug = nullptr; }
};

void addAttributeFake(gapi::VertexAttribDescriptor desc) {}

TEST_F(GeomTestFixture, createBuffer) {
  auto *shaderStub = new render::global::ShaderStub(gapi::ShaderType::UNDEF);
  EXPECT_CALL(*globalGapiPlug, createShader(testing::_)).WillRepeatedly(testing::Return(shaderStub));

  auto *shaderProgramStub = new render::global::ShaderProgramStub();
  EXPECT_CALL(*globalGapiPlug, createShaderProgram()).WillRepeatedly(testing::Return(shaderProgramStub));
  EXPECT_CALL(*shaderProgramStub, attach(shaderStub)).Times(2);
  EXPECT_CALL(*shaderProgramStub, link());
  EXPECT_CALL(*shaderProgramStub, isLinked()).WillOnce(testing::Return(true));
  EXPECT_CALL(*shaderProgramStub, validate());
  EXPECT_CALL(*shaderProgramStub, isValidated()).WillOnce(testing::Return(true));
  // EXPECT_CALL(*shaderProgramStub, use());
  // EXPECT_CALL(*shaderProgramStub, unuse());

  gapi::ShaderCreateInfoSet infoSet;
  infoSet.vs.type = gapi::ShaderType::VERT;
  infoSet.vs.code = "";
  infoSet.fs.type = gapi::ShaderType::FRAG;
  infoSet.fs.code = "";
  auto *effect = new render::Effect(globalGapiPlug, infoSet);

  auto *idGeneratorStub = new render::global::IdGeneratorStub();
  ON_CALL(*idGeneratorStub, newGuid()).WillByDefault(testing::Return(1));

  auto *bufferStub = new render::global::BufferStub();

  auto *vertexAttribLayoutStub = new render::global::VertexAttribLayoutStub();
  EXPECT_CALL(*vertexAttribLayoutStub, addAttribute(testing::_)).Times(testing::Exactly(4 /* кол.-во вызовов */));

  EXPECT_CALL(*globalGapiPlug, createIdGenerator()).WillRepeatedly(testing::Return(idGeneratorStub));
  EXPECT_CALL(*globalGapiPlug, createBuffer(testing::_, testing::_)).WillRepeatedly(testing::Return(bufferStub));
  EXPECT_CALL(*globalGapiPlug, createVertexAttribLayout(shaderProgramStub))
      .WillRepeatedly(testing::Return(vertexAttribLayoutStub));

  auto *geomBuilder = new render::GeomBuilder(globalGapiPlug, idGeneratorStub);

  geomBuilder->reserve(1);
  geomBuilder->reserve(render::Constants::MAX_BUFFER_OBJECTS + 10 /* Выходим за рамки допустимого */);

  auto geometries = geomBuilder->getGeometries();
  ASSERT_EQ(geometries.size(), render::Constants::MAX_BUFFER_OBJECTS);

  auto numInstances = 1;
  auto geomShape = std::make_shared<render::procedurals::prims::Quadrilateral<math::VertexColor>>(numInstances);
  std::static_pointer_cast<render::procedurals::prims::Quadrilateral<math::VertexColor>>(geomShape)
      ->useVertexSemanticSet({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});

  render::GeometryCreateInfo geomCreateInfo;
  geomCreateInfo.indexed = true;
  geomBuilder->getGeometry(0)->create(geomCreateInfo, effect, geomShape->getVertexAttribs());

  EXPECT_TRUE(geomBuilder->getGeometry(0)->getBuffer(render::Constants::IDX_VBO).has_value());
  EXPECT_TRUE(geomBuilder->getGeometry(0)->getBuffer(render::Constants::IDX_EBO).has_value());

  geomBuilder->getGeometry(1)->create(render::GeometryCreateInfo(), effect, geomShape->getVertexAttribs());

  EXPECT_TRUE(geomBuilder->getGeometry(1)->getBuffer(render::Constants::IDX_VBO).has_value());
  EXPECT_FALSE(geomBuilder->getGeometry(1)->getBuffer(render::Constants::IDX_EBO).has_value());

  SAFE_DELETE_OBJECT(vertexAttribLayoutStub);
  SAFE_DELETE_OBJECT(bufferStub);
  SAFE_DELETE_OBJECT(idGeneratorStub);
  SAFE_DELETE_OBJECT(geomBuilder);
  SAFE_DELETE_OBJECT(shaderStub);
  // SAFE_DELETE_OBJECT(shaderProgramStub);
  SAFE_DELETE_OBJECT(effect);
}
