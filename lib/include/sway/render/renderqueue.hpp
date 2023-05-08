#ifndef SWAY_RENDER_RENDERQUEUE_HPP
#define SWAY_RENDER_RENDERQUEUE_HPP

#include <sway/core/intrusive/priorities.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderQueue {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  RenderQueue();

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] priority Приоритет очереди.
   */
  RenderQueue(u32_t priority);

  /**
   * @brief Деструктор класса.
   *        Освобождает захваченные ресурсы.
   */
  ~RenderQueue();

  /**
   * @brief Добавляет подочередь @ref RenderSubqueue в группу.
   *
   * @param[in] subqueue Указатель на обьект класса подочереди, которой следует добавить в контейнер.
   * @sa removeSubqueue(const RenderSubqueueRef_t &)
   */
  void addSubqueue(const RenderSubqueueRef_t &subqueue);

  /**
   * @brief Удаляет подочередь @ref RenderSubqueue из группы.
   *
   * @param[in] subqueue Указатель на обьект класса подочереди, которой следует удалить из контейнера.
   * @sa addSubqueue(const RenderSubqueueRef_t &)
   */
  void removeSubqueue(const RenderSubqueueRef_t &subqueue);

  /**
   * @brief Получает коллекцию подочередей.
   *
   * @param[in] group Группа подочереди.
   */
  auto getSubqueues(RenderSubqueueGroup group) -> RenderSubqueueRefVec_t &;

  /**
   * @brief Устанавливает значение приоритета.
   *
   * @sa getPriority() const
   */
  void setPriority(u32_t priority) { priority_ = priority; }

  /**
   * @brief Получает значение приоритета.
   *
   * @sa setPriority(u32_t)
   */
  auto getPriority() const -> u32_t { return priority_; }

  struct PriorityInDescendingOrder {
    bool operator()(const RenderQueueRef_t &lhs, const RenderQueueRef_t &rhs) const {
      return lhs->getPriority() > rhs->getPriority();
    }
  };

private:
  u32_t priority_;  // Приоритет очереди.
  RenderSubqueueRefVec_t subqueues_[RENDER_SUBQUEUE_GROUP_COUNT];  // Контейнер подочередей.
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERQUEUE_HPP
