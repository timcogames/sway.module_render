#ifndef SWAY_RENDER_GEOMETRYVERTEXATTRIB_HPP
#define SWAY_RENDER_GEOMETRYVERTEXATTRIB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/vertexattrib.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TAttribFormat>
class GeometryVertexAttrib : public gapi::VertexAttrib {
public:
  using VertexAttribType_t = typename TAttribFormat::DataElementType_t;

  GeometryVertexAttrib(gapi::VertexSemantic semantic, i32_t reserve, bool normalized = false)
      : vertices_(nullptr)
      , reserve_(reserve)
      , capacity_(0)
      , counter_(0)
      , enabled_(false) {
    descriptor_ = gapi::VertexAttribDescriptor::merge<TAttribFormat>(semantic, normalized, true);
  }

  virtual ~GeometryVertexAttrib() { SAFE_DELETE_ARRAY(vertices_); }

  MTHD_OVERRIDE(void importRawdata(void *data, i32_t offset, i32_t vtx)) {
    for (auto i = 0; i < descriptor_.numComponents; ++i) {
      *((VertexAttribType_t *)data + offset + i) = vertices_[descriptor_.numComponents * vtx + i];
    }
  }

  void setVertexData(i32_t vtx, void *src) {
    for (auto i = 0; i < descriptor_.numComponents; ++i) {
      vertices_[descriptor_.numComponents * vtx + i] = ((VertexAttribType_t *)src)[i];
    }
  }

  MTHD_OVERRIDE(void importRawdata2(void *dst, i32_t offset, void *src)) {
    for (auto i = 0; i < descriptor_.numComponents; ++i) {
      *((VertexAttribType_t *)dst + offset + i) = ((VertexAttribType_t *)src)[i];
    }
  }

  // clang-format off
  MTHD_OVERRIDE(auto getComponent(u32_t idx) const -> void *) {  // clang-format on
    return (void **)(&vertices_[idx]);
  }

  // clang-format off
  MTHD_OVERRIDE(auto getDescriptor() -> gapi::VertexAttribDescriptor) {  // clang-format on
    return descriptor_;
  }

  MTHD_OVERRIDE(void use()) { enabled_ = true; }

  // clang-format off
  MTHD_OVERRIDE(auto getCapacity() -> i32_t) {  // clang-format on
    return capacity_;
  }

  // clang-format off
  MTHD_OVERRIDE(auto isEnabled() const -> bool) {  // clang-format on
    return enabled_;
  }

  void removeVtxData() { SAFE_DELETE_ARRAY(vertices_); }

  void addVtxData(TAttribFormat vec) {
    if (counter_ + 1 > capacity_) {
      reallocate_();
    }

    auto *dst = &vertices_[counter_ * descriptor_.numComponents];
    for (auto i = 0; i < descriptor_.numComponents; ++i) {
      *dst++ = vec[i];
    }

    counter_++;
  }

  [[nodiscard]]
  auto getNumOfVertices() const -> i32_t {
    return counter_;
  }

public:
  void reallocate_() {
    capacity_ = capacity_ == 0 ? reserve_ : capacity_ * 2;

    auto *tmp = new VertexAttribType_t[capacity_ * descriptor_.numComponents];
    if (counter_ != 0) {
      memcpy(tmp, vertices_, counter_ * descriptor_.stride);
    }

    SAFE_DELETE_ARRAY(vertices_);

    vertices_ = tmp;
  }

  gapi::VertexAttribDescriptor descriptor_;
  VertexAttribType_t *vertices_;  // Набор данных.
  i32_t reserve_;
  i32_t capacity_;
  i32_t counter_;
  bool enabled_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMETRYVERTEXATTRIB_HPP
