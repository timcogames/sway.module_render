#ifndef SWAY_GRAPHICS_RENDERSUBSYSTEM_H
#define SWAY_GRAPHICS_RENDERSUBSYSTEM_H

#include <sway/graphics/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class RenderSubsystem : public core::foundation::Object {
	DECLARE_OBJECT(RenderSubsystem, core::foundation::Object)

public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] context
	 *    Контекст подсистемы.
	 */
	RenderSubsystem(core::foundation::Context * context);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	virtual ~RenderSubsystem();

	/*!
	 * \brief
	 *    Создает новую очередь и добавляет её в контейнер.
	 *
	 * \return
	 *    Умный указатель на объект класса очереди.
	 */
	RenderQueueRef_t createQueue();

	/*!
	 * \brief
	 *    Получает очередь по индексу.
	 *
	 * \param[in] index
	 *    Индекс очереди.
	 * 
	 * \return
	 *    Умный указатель на объект класса очереди.
	 */
	RenderQueueRef_t getQueueByIdx(u32_t index);

	/*!
	 * \brief
	 *    Получает все очереди.
	 */
	RenderQueueRefVector_t getQueues();

	/*!
	 * \brief
	 *    Сортирует очереди по приоритету.
	 */
	void sortQueues();

	/*!
	 * \brief
	 *    Метод отрисовки.
	 */
	void render();

private:
	void _renderSubqueues(RenderQueueRef_t queue, u32_t group);

private:
	RenderQueueRefVector_t _queues; /*!< Контейнер очередей. */
	gapi::Capabilities * _caps;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERSUBSYSTEM_H
