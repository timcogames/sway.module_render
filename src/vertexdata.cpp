#include <sway/graphics/vertexdata.h>
#include <sway/graphics/vertexchannel.h>
#include <algorithm>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

VertexData::VertexData()
	: _vertexCount(0) {
	// Empty
}

VertexData::VertexData(u32_t count)
	: _vertexCount(count) {
	// Empty
}

VertexData::~VertexData() {
	// Empty
}

VertexChannelRefMap_t VertexData::getChannels() {
	return _channels;
}

VertexChannelRef_t VertexData::getChannel(gapi::VertexSemantic_t semantic) {
	return _channels[semantic];
}

u32_t VertexData::getVertexCount() const {
	return _vertexCount;
}

void * VertexData::getRaw() {
	void * dataArray = (void *) malloc(sizeof(math::VertexColor) * getVertexCount());

	u32_t offset = 0;
	for (int i = 0; i < getVertexCount(); ++i) {
		auto posAttribDescriptor = getChannel(gapi::VertexSemantic_t::kPosition)->getVertexAttribDescriptor();
		for (int num = 0; num < posAttribDescriptor.numComponents; ++num)
			*((f32_t *) dataArray + offset + num) = getChannel(gapi::VertexSemantic_t::kPosition)->getData(posAttribDescriptor.numComponents * i + num);

		offset += posAttribDescriptor.numComponents;

		auto colAttribDescriptor = getChannel(gapi::VertexSemantic_t::kColor)->getVertexAttribDescriptor();
		for (int num = 0; num < colAttribDescriptor.numComponents; ++num)
			*((f32_t *) dataArray + offset + num) = getChannel(gapi::VertexSemantic_t::kColor)->getData(colAttribDescriptor.numComponents * i + num);

		offset += colAttribDescriptor.numComponents;
	}

	// auto data = (f32_t *)dataArray;
	// printf("{%f, %f, %f}\n", data[ 0], data[ 1], data[ 2]);
	// printf("{%f, %f, %f}\n", data[ 7], data[ 8], data[ 9]);
	// printf("{%f, %f, %f}\n", data[14], data[15], data[16]);
	// printf("{%f, %f, %f}\n", data[21], data[22], data[23]);

	return dataArray;
}

void VertexData::addTriIndices(u32_t a, u32_t b, u32_t c) {
	addIndex(a);
	addIndex(b);
	addIndex(c);
}

void VertexData::addIndex(u32_t index) {
	_indices.push_back(index);
}

IndexVec_t & VertexData::getIndices() {
	return _indices;
}

u32_t VertexData::getIndexCount() const {
	return _indices.size();
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
