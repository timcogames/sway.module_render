#ifndef SWAY_GRAPHICS_VERTEXDATA_H
#define SWAY_GRAPHICS_VERTEXDATA_H

#include <sway/graphics/prereqs.h>
#include <sway/graphics/vertexchannel.h>
#include <sway/core.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class VertexData {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	VertexData();

	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	VertexData(u32_t num);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *    Освобождает захваченные ресурсы.
	 */
	~VertexData();

	template<typename TYPE>
	VertexChannelRef_t createChannel(gapi::VertexSemantic_t semantic);

	VertexChannelRefMap_t getChannels();

	u32_t getVertexCount() const;

	void * getRaw();

private:
	VertexChannelRefMap_t _channels;
	u32_t _vertexCount;
};

#include <sway/graphics/vertexdata.inl>

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_VERTEXDATA_H
