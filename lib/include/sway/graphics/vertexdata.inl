#include <sway/graphics/vertexchannel.hpp>
#include <sway/graphics/vertexdata.hpp>

template <typename TYPE>
VertexChannelRef_t VertexData::createChannel(gapi::VertexSemantic_t semantic, u32_t count) {
  auto channel = std::make_shared<TVertexChannel<TYPE>>(semantic, count);
  _channels[semantic] = channel;
  return channel;
}
