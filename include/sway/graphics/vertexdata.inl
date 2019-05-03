#include <sway/graphics/vertexdata.h>
#include <sway/graphics/vertexchannel.h>

template<typename TYPE>
VertexChannelRef_t VertexData::createChannel(gapi::VertexSemantic_t semantic) {
	auto channel = std::make_shared<TVertexChannel<TYPE>>(semantic, _vertexCount);
	_channels[semantic] = channel;
	return channel;
}
