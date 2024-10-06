#ifndef SWAY_RENDER_RENDERQUEUE_HPP
#define SWAY_RENDER_RENDERQUEUE_HPP

#include <sway/core/intrusive/priorities.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class RenderQueue {
  DECLARE_CLASS_POINTER_ALIASES(RenderQueue)

public:
#pragma region "Ctors/Dtor"

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

#pragma endregion

  /**
   * @brief Добавляет подочередь @ref RenderSubqueue в группу.
   *
   * @param[in] subqueue Указатель на обьект класса подочереди, которой следует добавить в контейнер.
   * @sa removeSubqueue(const RenderSubqueue::SharedPtr_t &)
   */
  void addSubqueue(const RenderSubqueue::SharedPtr_t &subqueue);

  /**
   * @brief Удаляет подочередь @ref RenderSubqueue из группы.
   *
   * @param[in] subqueue Указатель на обьект класса подочереди, которой следует удалить из контейнера.
   * @sa addSubqueue(const RenderSubqueue::SharedPtr_t &)
   */
  void removeSubqueue(const RenderSubqueue::SharedPtr_t &subqueue);

  /**
   * @brief Получает коллекцию подочередей.
   *
   * @param[in] group Группа подочереди.
   */
  auto getSubqueues(RenderSubqueueGroup group) -> RenderSubqueueSharedPtrVec_t &;

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
  [[nodiscard]]
  auto getPriority() const -> u32_t {
    return priority_;
  }

  struct PriorityInDescendingOrder {
    bool operator()(const RenderQueue::SharedPtr_t &lhs, const RenderQueue::SharedPtr_t &rhs) const {
      return lhs->getPriority() > rhs->getPriority();
    }
  };

private:
  u32_t priority_;  // Приоритет очереди.
  RenderSubqueue::SharedPtrVec_t subqueues_[RENDER_SUBQUEUE_GROUP_COUNT];  // Контейнер подочередей.
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERQUEUE_HPP
