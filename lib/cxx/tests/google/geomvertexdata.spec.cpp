#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace sway;

TEST(GeomVertexData, create_attrib) {
  auto numVerts = 4;
  auto geomVertexData = std::make_shared<render::GeomVertexData<math::VertexColor>>(numVerts);

  auto pos = geomVertexData->template createAttrib<math::vec3f_t>(gapi::VertexSemantic::POS);
  ASSERT_FALSE(pos->enabled());

  pos->setData(0, math::vec3f_t(1.0F, 1.0F, 1.0F).asDataPtr());
  pos->setData(1, math::vec3f_t(1.1F, 1.1F, 1.1F).asDataPtr());
  pos->setData(2, math::vec3f_t(1.2F, 1.2F, 1.2F).asDataPtr());
  pos->setData(3, math::vec3f_t(1.3F, 1.3F, 1.3F).asDataPtr());

  auto col = geomVertexData->template createAttrib<math::vec4f_t>(gapi::VertexSemantic::COL);
  ASSERT_FALSE(col->enabled());

  col->setData(0, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).asDataPtr());
  col->setData(1, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).asDataPtr());
  col->setData(2, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).asDataPtr());
  col->setData(3, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).asDataPtr());

  geomVertexData->useSemanticSet({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  ASSERT_TRUE(pos->enabled());
  ASSERT_TRUE(col->enabled());

  // auto data = (math::VertexColor *)geomVertexData->getVertices();
  // for (auto i = 0; i < numVerts; i++) {
  //   std::cout << data[i] << std::endl;
  // }

  // free(data);
}
