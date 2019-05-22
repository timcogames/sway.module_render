#ifndef SWAY_GRAPHICS_PRIMITIVES_QUAD_H
#define SWAY_GRAPHICS_PRIMITIVES_QUAD_H

#include <sway/math.h>
#include <sway/graphics/vertexdata.h>
#include <sway/graphics/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)
NAMESPACE_BEGIN(primitives)

class Quad : public VertexData {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	Quad(f32_t width, f32_t height);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *    Освобождает захваченные ресурсы.
	 */
	virtual ~Quad();
};

NAMESPACE_END(primitives)
NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_PRIMITIVES_QUAD_H
