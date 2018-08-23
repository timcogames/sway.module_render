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
	 * \param[in] group
	 *    Группа подочереди.
	 */
	RenderSubqueue(RenderSubqueueGroup_t group = RenderSubqueueGroup_t::kOpaque);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	~RenderSubqueue();

	/*!
	 * \brief
	 *    Добавляет отрисовываемый объект.
	 * 
	 * \param[in] drawable
	 *    Отрисовываемый объект.
	 */
	void addDrawable(DrawableRef_t drawable);

	/*!
	 * \brief
	 *    Метод отрисовки.
	 */
	void render();

	/*!
	 * \brief
	 *    Устанавливает группу подочереди.
	 * 
	 * \param[in] group
	 *    Группа подочереди.
	 */
	void setGroup(RenderSubqueueGroup_t group);

	/*!
	 * \brief
	 *    Получает группу подочереди.
	 */
	RenderSubqueueGroup_t getGroup() const;

private:
	gapi::DrawCallRef_t _drawCall;
	DrawableRefVec_t _drawables;
	RenderSubqueueGroup_t _group; /*!< Группа подочереди. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERSUBQUEUE_H
