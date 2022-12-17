#include <sway/graphics/vertexchannel.hpp>

template <typename TAttributeFormatType>
GeometryVertexChannel<TAttributeFormatType>::GeometryVertexChannel(gapi::VertexSemantic_t semantic, std::size_t reserve)
    : vertexReserve_(reserve)
    , vertexData_(0)
    , vertexCount_(0) {
  descriptor_ = gapi::VertexAttributeDescriptor::merge<TAttributeFormatType>(semantic, false, true);
}

template <typename TAttributeFormatType>
void GeometryVertexChannel<TAttributeFormatType>::addAnyData(f32_t *data, int &capacity) {
  if (vertexCount_ + 1 > capacity) {
    reallocate_(capacity);
  }

  auto *dst = &vertexData_[vertexCount_ * descriptor_.numComponents];
  for (int i = 0; i < descriptor_.numComponents; ++i) {
    *dst++ = data[i];
  }

  vertexCount_++;
}

template <typename TAttributeFormatType>
auto GeometryVertexChannel<TAttributeFormatType>::getData(u32_t idx) const -> f32_t {
  return vertexData_[idx];
}
