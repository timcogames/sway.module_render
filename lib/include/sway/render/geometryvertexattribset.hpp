#ifndef SWAY_RENDER_GEOMETRYVERTEXATTRIBSET_HPP
#define SWAY_RENDER_GEOMETRYVERTEXATTRIBSET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/geometryvertexattrib.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct GeometryVertexAttribSet {
  std::shared_ptr<GeometryVertexAttrib<math::vec3f_t>> pos;
  std::shared_ptr<GeometryVertexAttrib<math::vec3f_t>> col;
  std::shared_ptr<GeometryVertexAttrib<math::vec2f_t>> tex;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMETRYVERTEXATTRIBSET_HPP
