#include <sway/graphics/vertexchannel.hpp>
#include <sway/graphics/vertexdata.hpp>

template <typename TAttributeFormatType>
auto VertexData::createChannel(gapi::VertexSemantic_t semantic, u32_t count) -> VertexChannelRef_t {
  auto channel = std::make_shared<GeometryVertexChannel<TAttributeFormatType>>(semantic, count);
  channels_[semantic] = channel;
  return channel;
}
