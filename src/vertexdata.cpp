#include <sway/graphics/vertexdata.h>
#include <sway/graphics/vertexchannel.h>
#include <algorithm>

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

VertexChannelRefMap_t VertexData::getChannels() {
	return _channels;
}

u32_t VertexData::getVertexCount() const {
	return _vertexCount;
}

void * VertexData::getRaw() {
	u32_t channelOffset = 0;
	void * dataArray = (void *) malloc(sizeof(math::VertexPosition) * getVertexCount());
	for (int vertexIdx = 0; vertexIdx < getVertexCount(); ++vertexIdx) {
		for (const auto & channel : getChannels()) {
			auto attribDescriptor = channel.second->getVertexAttribDescriptor();
			auto component = static_cast<f32_t *>(channel.second->getData(vertexIdx));

			for (int num = 0; num < attribDescriptor.numComponents; ++num)
				*((f32_t *) dataArray + channelOffset + num) = component[num];

			channelOffset += attribDescriptor.numComponents;
		}
	}

	return dataArray;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
