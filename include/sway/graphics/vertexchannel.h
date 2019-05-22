#ifndef SWAY_GRAPHICS_VERTEXCHANNEL_H
#define SWAY_GRAPHICS_VERTEXCHANNEL_H

#include <sway/graphics/prereqs.h>
#include <sway/core.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class IVertexChannelBase {
public:
	/*!
	 * \brief
	 *    Виртуальный деструктор класса.
	 */
	virtual ~IVertexChannelBase() {};

	virtual void addAnyData(f32_t * data, int & capacity) = 0;

	virtual f32_t getData(u32_t idx) const = 0;

	virtual s32_t getVertCount() const = 0;

	virtual gapi::VertexAttributeDescriptor getVertexAttribDescriptor() = 0;
};

template<typename TYPE>
class TVertexChannel : public IVertexChannelBase {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	TVertexChannel(gapi::VertexSemantic_t semantic, std::size_t reserve = 8);

	/*!
	 * \brief
	 *    Деструктор класса.
	 */
	virtual ~TVertexChannel() = default;

	virtual void addAnyData(f32_t * data, int & capacity);

	virtual f32_t getData(u32_t idx) const;

	virtual s32_t getVertCount() const;

	virtual gapi::VertexAttributeDescriptor getVertexAttribDescriptor();

private:
	void _reallocate(s32_t & capacity) {
		capacity = !capacity ? _vertexReserve : capacity * 2;

		f32_t * tmp = new f32_t[capacity * _descriptor.numComponents];
		if (_vertexCount)
			memcpy(tmp, _vertexData, _vertexCount * _descriptor.stride);

		SAFE_DELETE_ARRAY(_vertexData);

		_vertexData = tmp;
	}

private:
	gapi::VertexAttributeDescriptor _descriptor;
	std::size_t _vertexReserve;
	f32_t * _vertexData; /*!< Набор данных. */
	s32_t _vertexCount;
};

#include <sway/graphics/vertexchannel.inl>

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_VERTEXCHANNEL_H
