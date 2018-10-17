#ifndef SWAY_GRAPHICS_DRAWABLE_H
#define SWAY_GRAPHICS_DRAWABLE_H

#include <sway/graphics/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Drawable {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Drawable(MaterialRef_t material, bool indexed);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	~Drawable();

	void create(const gapi::BufferCreateInfoSet & infoSet);

	/*!
	 * \brief 
	 *   Получает указатель на объект вершинного буфера.
	 *
	 * \sa 
	 *   getIBO()
	 */
	gapi::BufferRef_t getVBO();

	/*!
	 * \brief 
	 *   Получает указатель на объект индексного буфера.
	 *
	 * \sa 
	 *   getVBO()
	 */
	gapi::BufferRef_t getIBO();

	gapi::VertexLayoutRef_t getVertexLayout();

	MaterialRef_t getMaterial();

private:
	gapi::BufferRef_t _vbo; /*!< Объект буфера вершин. */
	gapi::BufferRef_t _ibo; /*!< Объект буфера индексов. */
	gapi::VertexLayoutRef_t _vlayout;
	MaterialRef_t _material;
	bool _indexed;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_DRAWABLE_H
