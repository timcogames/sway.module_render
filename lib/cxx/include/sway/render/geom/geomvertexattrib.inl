#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/geom/geomvertexattrib.hpp>
#include <sway/render/geom/geomvertexdatabase.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TAttribFormat>
GeomVertexAttrib<TAttribFormat>::GeomVertexAttrib(
    GeomVertexDataBase *owner, gapi::VertexSemantic semantic, bool normalized)
    : owner_(owner)
    , descriptor_(gapi::VertexAttribDescriptor::merge<TAttribFormat>(semantic, normalized, false)) {
  vertices_ = new VertexAttribType_t[owner_->getVtxSize() * sizeof(VertexAttribType_t)];
}

template <typename TAttribFormat>
void GeomVertexAttrib<TAttribFormat>::setData(u32_t idx, void *val) {
  for (auto i = 0; i < descriptor_.numComponents; ++i) {
    vertices_[descriptor_.numComponents * idx + i] = ((VertexAttribType_t *)val)[i];
  }
}

template <typename TAttribFormat>
void GeomVertexAttrib<TAttribFormat>::getData(void *dst, i32_t offset, i32_t idx) {
  for (auto i = 0; i < descriptor_.numComponents; ++i) {
    *((VertexAttribType_t *)dst + offset + i) = vertices_[descriptor_.numComponents * idx + i];
  }
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
