#ifndef SWAY_GRAPHICS_VERTEXCHANNEL_H
#define SWAY_GRAPHICS_VERTEXCHANNEL_H

#include <sway/graphics/prereqs.h>
#include <sway/core.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

template<typename TYPE>
class TVertexChannel {
public:
	/*!
	 * \brief Конструктор класса.
	 *        Выполняет инициализацию нового экземпляра класса.
	 */
	TVertexChannel(gapi::VertexSemantic_t semantic, std::size_t num) {
		_descriptor = gapi::VertexAttribute::merge<TYPE>(semantic, false, true);
		_data.reserve(num);
	}

	/*!
	 * \brief Деструктор класса.
	 */
	~TVertexChannel() = default;

	std::size_t addAnyData(float * data) {
		_data.push_back(data);
		return _data.size() - 1;
	}

	gapi::VertexAttributeDescriptor getVertexAttribDescriptor() {
		return _descriptor;
	}

	void * getData(u32_t idx) const {
		if (idx >= _data.size())
			throw std::runtime_error("Data out of range.");

		return _data[idx];
	}

private:
	gapi::VertexAttributeDescriptor _descriptor;
	std::vector<float *> _data;
};

#include <sway/graphics/vertexchannel.inl>

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_VERTEXCHANNEL_H
