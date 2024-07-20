#ifndef SWAY_RENDER_GEOMVERTEXATTRIBBASE_HPP
#define SWAY_RENDER_GEOMVERTEXATTRIBBASE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class GeomVertexAttribBase {
public:
  PURE_VIRTUAL(void setData(u32_t idx, void *val));

  PURE_VIRTUAL(void getData(void *dst, i32_t offset, i32_t idx));

  PURE_VIRTUAL(void importRawdata2(void *dst, i32_t offset, void *src));

  // clang-format off
  PURE_VIRTUAL(auto getDescriptor() -> gapi::VertexAttribDescriptor);  // clang-format on

  PURE_VIRTUAL(void use());

  // clang-format off
  PURE_VIRTUAL(auto enabled() const -> bool);  // clang-format on
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMVERTEXATTRIBBASE_HPP
