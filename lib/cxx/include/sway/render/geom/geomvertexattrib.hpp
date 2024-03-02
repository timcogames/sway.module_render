#ifndef SWAY_RENDER_GEOMVERTEXATTRIB_HPP
#define SWAY_RENDER_GEOMVERTEXATTRIB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/vertexattrib.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class VertexAttrib {
public:
  PURE_VIRTUAL(void setData(u32_t idx, void *val));

  PURE_VIRTUAL(void getData(void *dst, s32_t offset, s32_t idx));

  // clang-format off
  PURE_VIRTUAL(auto getDescriptor() -> gapi::VertexAttribDescriptor);  // clang-format on

  PURE_VIRTUAL(void use());

  // clang-format off
  PURE_VIRTUAL(auto enabled() const -> bool);  // clang-format on
};

class GeomVertexDataBase;

template <typename TAttribFormat>
class GeomVertexAttrib : public VertexAttrib {
public:
  using VertexAttribType_t = typename TAttribFormat::DataElementType_t;

  GeomVertexAttrib(GeomVertexDataBase *owner, gapi::VertexSemantic semantic, bool normalized);

  virtual ~GeomVertexAttrib() { SAFE_DELETE_ARRAY(data_); }

  MTHD_OVERRIDE(void setData(u32_t idx, void *val)) {
    for (auto i = 0; i < descriptor_.numComponents; ++i) {
      data_[descriptor_.numComponents * idx + i] = ((VertexAttribType_t *)val)[i];
    }
  }

  MTHD_OVERRIDE(void getData(void *dst, s32_t offset, s32_t idx)) {
    for (auto i = 0; i < descriptor_.numComponents; ++i) {
      *((VertexAttribType_t *)dst + offset + i) = data_[descriptor_.numComponents * idx + i];
    }
  }

  // clang-format off
  MTHD_OVERRIDE(auto getDescriptor() -> gapi::VertexAttribDescriptor) {  // clang-format on
    return descriptor_;
  }

  MTHD_OVERRIDE(void use()) { enabled_ = true; }

  // clang-format off
  MTHD_OVERRIDE(auto enabled() const -> bool) {  // clang-format on
    return enabled_;
  }

private:
  GeomVertexDataBase *owner_;
  gapi::VertexAttribDescriptor descriptor_;
  VertexAttribType_t *data_;
  bool enabled_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#include <sway/render/geom/geomvertexattrib.inl>

#endif  // SWAY_RENDER_GEOMVERTEXATTRIB_HPP
