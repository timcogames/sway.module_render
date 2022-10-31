#include <sway/graphics/vertexchannel.hpp>

template <typename TYPE>
TVertexChannel<TYPE>::TVertexChannel(gapi::VertexSemantic_t semantic, std::size_t reserve)
    : vertexReserve_(reserve)
    , vertexData_(0)
    , vertexCount_(0) {
  descriptor_ = gapi::VertexAttribute::merge<TYPE>(semantic, false, true);
}

template <typename TYPE>
void TVertexChannel<TYPE>::addAnyData(f32_t *data, int &capacity) {
  if (vertexCount_ + 1 > capacity) {
    reallocate_(capacity);
  }

  f32_t *dst = &vertexData_[vertexCount_ * descriptor_.numComponents];
  for (int i = 0; i < descriptor_.numComponents; ++i)
    *dst++ = data[i];

  vertexCount_++;
}

template <typename TYPE>
f32_t TVertexChannel<TYPE>::getData(u32_t idx) const {
  return vertexData_[idx];
}

template <typename TYPE>
s32_t TVertexChannel<TYPE>::getVertCount() const {
  return vertexCount_;
}

template <typename TYPE>
gapi::VertexAttributeDescriptor TVertexChannel<TYPE>::getVertexAttribDescriptor() {
  return descriptor_;
}
