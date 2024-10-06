#ifndef SWAY_RENDER_GEOMVERTEXATTRIBBASE_HPP
#define SWAY_RENDER_GEOMVERTEXATTRIBBASE_HPP

#include <sway/render/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class GeomVertexAttribBase {
  DECLARE_CLASS_POINTER_ALIASES(GeomVertexAttribBase)

public:
  PURE_VIRTUAL(void setData(u32_t idx, void *val));

  PURE_VIRTUAL(void getData(void *dst, i32_t offset, i32_t idx));

  PURE_VIRTUAL(void importRawdata2(void *dst, i32_t offset, void *src));

  PURE_VIRTUAL(auto getDescriptor() -> gapi::VertexAttribDescriptor);

  PURE_VIRTUAL(void use());

  PURE_VIRTUAL(auto enabled() const -> bool);
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_GEOMVERTEXATTRIBBASE_HPP
