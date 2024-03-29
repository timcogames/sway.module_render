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
  GeometryVertexAttrib(gapi::VertexSemantic semantic, s32_t reserve)
      : vertices_(nullptr)
      , reserve_(reserve)
      , capacity_(0)
      , counter_(0)
      , enabled_(false) {
    descriptor_ = gapi::VertexAttribDescriptor::merge<TAttribFormat>(semantic, false, true);
  }

  ~GeometryVertexAttrib() { SAFE_DELETE_ARRAY(vertices_); }

  MTHD_OVERRIDE(void importRawdata(void *data, s32_t offset, s32_t vtx)) {
    for (auto i = 0; i < descriptor_.numComponents; ++i) {
      auto component = vertices_[descriptor_.numComponents * vtx + i];
      *((typename TAttribFormat::type_t *)data + offset + i) = component;
    }
  }

  MTHD_OVERRIDE(void importRawdata2(void *data, s32_t offset, typename TAttribFormat::type_t *vertices)) {
    for (auto i = 0; i < descriptor_.numComponents; ++i) {
      *((typename TAttribFormat::type_t *)data + offset + i) = vertices[i];
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
  MTHD_OVERRIDE(auto getCapacity() -> s32_t) {  // clang-format on
    return capacity_;
  }

  // clang-format off
  MTHD_OVERRIDE(auto isEnabled() const -> bool) {  // clang-format on
    return enabled_;
  }

  void addVtxData(TAttribFormat vec) {
    if (counter_ + 1 > capacity_) {
      reallocate_();
    }

    auto *dst = &vertices_[counter_ * descriptor_.numComponents];
    for (auto i = 0; i < descriptor_.numComponents; ++i) {
      *dst++ = vec.getData()[i];
    }

    counter_++;
  }

  [[nodiscard]] auto getNumOfVertices() const -> s32_t { return counter_; }

private:
  void reallocate_() {
    capacity_ = capacity_ == 0 ? reserve_ : capacity_ * 2;

    auto *tmp = new typename TAttribFormat::type_t[capacity_ * descriptor_.numComponents];
    if (counter_ != 0) {
      memcpy(tmp, vertices_, counter_ * descriptor_.stride);
    }

    SAFE_DELETE_ARRAY(vertices_);

    vertices_ = tmp;
  }

  gapi::VertexAttribDescriptor descriptor_;
  typename TAttribFormat::type_t *vertices_;  // Набор данных.
  s32_t reserve_;
  s32_t capacity_;
  s32_t counter_;
  bool enabled_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMETRYVERTEXATTRIB_HPP
