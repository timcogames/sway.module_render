#include <sway/graphics/vertexdata.h>
#include <sway/graphics/vertexchannel.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

VertexData::VertexData()
	: _vertexCount(0) {
	// Empty
}

VertexData::VertexData(u32_t num)
	: _vertexCount(num) {
	// Empty
}

VertexData::~VertexData() {
	// Empty
}

VertexChannelRefUmap_t VertexData::getChannels() const {
	return _channels;
}

u32_t VertexData::getVertexCount() const {
	return _vertexCount;
}

f32_t * VertexData::getRaw() {
	u32_t channelOffset = 0;
	f32_t * dataArray = (f32_t *) malloc(sizeof(math::VertexPosition) * getVertexCount());
	for (int vertexIdx = 0; vertexIdx < getVertexCount(); ++vertexIdx) {
		BOOST_FOREACH (auto channel, getChannels() | boost::adaptors::map_values) {
			auto attribDescriptor = channel->getVertexAttribDescriptor();
			auto component = static_cast<f32_t *>(channel->getData(vertexIdx));

			for (int num = 0; num < attribDescriptor.numComponents; ++num) {
				*((f32_t *) dataArray + channelOffset + num) = component[num];
			}

			channelOffset += attribDescriptor.numComponents;
		}
	}

	return dataArray;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
