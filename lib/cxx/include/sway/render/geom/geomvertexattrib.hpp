#ifndef SWAY_RENDER_GEOMVERTEXATTRIB_HPP
#define SWAY_RENDER_GEOMVERTEXATTRIB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/geom/geomvertexattribbase.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class GeomVertexDataBase;

template <typename TAttribFormat>
class GeomVertexAttrib : public GeomVertexAttribBase {
public:
  using VertexAttribType_t = typename TAttribFormat::DataElementType_t;

  GeomVertexAttrib(GeomVertexDataBase *owner, gapi::VertexSemantic semantic, bool normalized);

  virtual ~GeomVertexAttrib() { SAFE_DELETE_ARRAY(vertices_); }

  MTHD_OVERRIDE(void setData(u32_t idx, void *val));

  MTHD_OVERRIDE(void getData(void *dst, i32_t offset, i32_t idx));

  MTHD_OVERRIDE(void importRawdata2(void *dst, i32_t offset, void *src)) {
    for (auto i = 0; i < descriptor_.numComponents; ++i) {
      *((VertexAttribType_t *)dst + offset + i) = ((VertexAttribType_t *)src)[i];
    }
  }

  MTHD_OVERRIDE(auto getDescriptor() -> gapi::VertexAttribDescriptor) { return descriptor_; }

  MTHD_OVERRIDE(void use()) { descriptor_.enabled = true; }

  MTHD_OVERRIDE(auto enabled() const -> bool) { return descriptor_.enabled; }

private:
  GeomVertexDataBase *owner_;
  gapi::VertexAttribDescriptor descriptor_;
  VertexAttribType_t *vertices_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#include <sway/render/geom/geomvertexattrib.inl>

#endif  // SWAY_RENDER_GEOMVERTEXATTRIB_HPP
