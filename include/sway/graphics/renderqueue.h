#ifndef SWAY_GRAPHICS_RENDERQUEUE_H
#define SWAY_GRAPHICS_RENDERQUEUE_H

#include <sway/graphics/rendersubqueuegroups.h>
#include <sway/graphics/prereqs.h>
#include <sway/core/intrusive/priorities.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class RenderQueue {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] priority
	 *    Приоритет очереди.
	 */
	RenderQueue(u32_t priority = core::intrusive::kPriority_Normal);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	~RenderQueue();

	/*!
	 * \brief
	 *    Добавляет подочередь \ref RenderSubqueue в группу.
	 *
	 * \param[in] subqueue
	 *    Указатель на обьект класса подочереди, которой следует добавить в контейнер.
	 * 
	 * \sa
	 *    removeSubqueue(const RenderSubqueueRef_t &)
	 */
	void addSubqueue(const RenderSubqueueRef_t & subqueue);

	/*!
	 * \brief
	 *    Удаляет подочередь \ref RenderSubqueue из группы.
	 *
	 * \param[in] subqueue
	 *    Указатель на обьект класса подочереди, которой следует удалить из контейнера.
	 * 
	 * \sa
	 *    addSubqueue(const RenderSubqueueRef_t &)
	 */
	void removeSubqueue(const RenderSubqueueRef_t & subqueue);

	/*!
	 * \brief
	 *    Получает коллекцию подочередей.
	 *
	 * \param[in] group
	 *    Группа подочереди.
	 */
	RenderSubqueueRefVec_t & getSubqueues(RenderSubqueueGroup_t group);

	/*!
	 * \brief
	 *    Устанавливает значение приоритета.
	 * 
	 * \sa
	 *    getPriority() const
	 */
	void setPriority(u32_t priority);

	/*!
	 * \brief
	 *    Получает значение приоритета.
	 * 
	 * \sa
	 *    setPriority(u32_t)
	 */
	u32_t getPriority() const;

	struct PriorityInDescendingOrder {
		bool operator()(const RenderQueueRef_t & lhs, const RenderQueueRef_t & rhs) const {
			return lhs->getPriority() > rhs->getPriority();
		}
	};

  private:
	u32_t _priority; /*!< Приоритет очереди. */
	RenderSubqueueRefVec_t _subqueues[MAX_RENDER_SUBQUEUE_GROUP]; /*!< Контейнер подочередей. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERQUEUE_H
