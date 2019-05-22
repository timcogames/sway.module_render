#include <sway/graphics/vertexchannel.h>

template<typename TYPE>
TVertexChannel<TYPE>::TVertexChannel(gapi::VertexSemantic_t semantic, std::size_t reserve)
	: _vertexReserve(reserve)
	, _vertexData(0)
	, _vertexCount(0) {
	_descriptor = gapi::VertexAttribute::merge<TYPE>(semantic, false, true);
}

template<typename TYPE>
void TVertexChannel<TYPE>::addAnyData(f32_t * data, int & capacity) {
	if (_vertexCount + 1 > capacity)
		_reallocate(capacity);

	f32_t * dst = &_vertexData[_vertexCount * _descriptor.numComponents];
	for (int i = 0; i < _descriptor.numComponents; ++i)
		*dst++ = data[i];

	_vertexCount++;
}

template<typename TYPE>
f32_t TVertexChannel<TYPE>::getData(u32_t idx) const {
	return _vertexData[idx];
}

template<typename TYPE>
s32_t TVertexChannel<TYPE>::getVertCount() const {
	return _vertexCount;
}

template<typename TYPE>
gapi::VertexAttributeDescriptor TVertexChannel<TYPE>::getVertexAttribDescriptor() {
	return _descriptor;
}
