#include <sway/graphics/vertexchannel.hpp>
#include <sway/graphics/vertexdata.hpp>

#include <algorithm>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

VertexData::VertexData()
    : vertexCount_(0) {}

VertexData::VertexData(s32_t count)
    : vertexCount_(count) {}

auto VertexData::getRaw() -> void * {
  void *dataArray = (void *)malloc(sizeof(math::VertexColor) * getVertexCount());

  u32_t offset = 0;
  for (auto i = 0; i < getVertexCount(); ++i) {
    auto posAttribDescriptor = getChannel(gapi::VertexSemantic_t::Position)->getVertexAttribDescriptor();
    for (auto num = 0; num < posAttribDescriptor.numComponents; ++num) {
      *((f32_t *)dataArray + offset + num) =
          getChannel(gapi::VertexSemantic_t::Position)->getData(posAttribDescriptor.numComponents * i + num);
    }

    offset += posAttribDescriptor.numComponents;

    auto colAttribDescriptor = getChannel(gapi::VertexSemantic_t::Color)->getVertexAttribDescriptor();
    for (auto num = 0; num < colAttribDescriptor.numComponents; ++num) {
      *((f32_t *)dataArray + offset + num) =
          getChannel(gapi::VertexSemantic_t::Color)->getData(colAttribDescriptor.numComponents * i + num);
    }

    offset += colAttribDescriptor.numComponents;
  }

  return dataArray;
}

void VertexData::addTriIndices(u32_t a, u32_t b, u32_t c) {
  addIndex(a);
  addIndex(b);
  addIndex(c);
}

void VertexData::addIndex(u32_t index) { indices_.push_back(index); }

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
