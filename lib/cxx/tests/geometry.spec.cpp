#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geombuilder.hpp>
#include <sway/render/geom/geomvertexattrib.hpp>
#include <sway/render/geom/geomvertexdata.hpp>
#include <sway/render/global.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace sway;

TEST(Geom, create) {
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

  auto data = (math::VertexColor *)geomVertexData->data();
  for (auto i = 0; i < numVerts; i++) {
    std::cout << data[i] << std::endl;
  }

  free(data);
}

render::global::GapiPluginFunctionSet *globalGapiPlug;

class GeomTestFixture : public testing::Test {
protected:
  render::global::MockPluginFunctionSet mockedGapiPlug;

  void SetUp() { globalGapiPlug = &mockedGapiPlug; }

  void TearDown() { globalGapiPlug = nullptr; }
};

TEST_F(GeomTestFixture, createBuffer) {
  auto *idGeneratorStub = new render::global::IdGeneratorStub();
  ON_CALL(*idGeneratorStub, newGuid()).WillByDefault(testing::Return(1));

  auto *bufferStub = new render::global::BufferStub();

  EXPECT_CALL(*globalGapiPlug, createIdGenerator()).WillRepeatedly(testing::Return(idGeneratorStub));
  EXPECT_CALL(*globalGapiPlug, createBuffer(testing::_, testing::_)).WillRepeatedly(testing::Return(bufferStub));

  auto *geomBuilder = new render::GeomBuilder(globalGapiPlug, idGeneratorStub);

  geomBuilder->reserve(1);
  geomBuilder->reserve(render::Constants::MAX_BUFFER_OBJECTS + 10 /* Выходим за рамки допустимого */);

  auto geometries = geomBuilder->getGeometries();
  ASSERT_EQ(geometries.size(), render::Constants::MAX_BUFFER_OBJECTS);

  render::GeometryCreateInfo geomCreateInfo;
  geomCreateInfo.indexed = true;
  geomBuilder->getGeometry(0)->create(geomCreateInfo);

  EXPECT_TRUE(geomBuilder->getGeometry(0)->getBuffer(render::Constants::IDX_VBO).has_value());
  EXPECT_TRUE(geomBuilder->getGeometry(0)->getBuffer(render::Constants::IDX_IBO).has_value());

  geomBuilder->getGeometry(1)->create(render::GeometryCreateInfo());

  EXPECT_TRUE(geomBuilder->getGeometry(1)->getBuffer(render::Constants::IDX_VBO).has_value());
  EXPECT_FALSE(geomBuilder->getGeometry(1)->getBuffer(render::Constants::IDX_IBO).has_value());

  SAFE_DELETE_OBJECT(geomBuilder);
  SAFE_DELETE_OBJECT(bufferStub);
  SAFE_DELETE_OBJECT(idGeneratorStub);
}
