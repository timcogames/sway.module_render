#ifndef SWAY_GRAPHICS_RENDERSUBQUEUE_H
#define SWAY_GRAPHICS_RENDERSUBQUEUE_H

#include <sway/graphics/prereqs.h>
#include <sway/graphics/rendersubqueuegroups.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class RenderSubqueue {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] groupIdx
	 *    Индекс группы.
	 */
	RenderSubqueue(u32_t groupIdx = kRenderSubqueueGroup_Opaque);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	~RenderSubqueue();

	void addDrawable(DrawableRef_t drawable);

	/*!
	 * \brief
	 *    Метод отрисовки.
	 */
	void render();

	/*!
	 * \brief
	 *    Устанавливает индекс группы.
	 */
	void setGroupIdx(u32_t groupIdx);

	/*!
	 * \brief
	 *    Получает индекс группы.
	 */
	u32_t getGroupIdx() const;

private:
	u32_t _group; /*!< Индекс группы подочереди. */
	DrawableRefVector_t _drawables;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERSUBQUEUE_H
