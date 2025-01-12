#ifndef SWAY_RENDER_RENDERQUEUE_HPP
#define SWAY_RENDER_RENDERQUEUE_HPP

#include <sway/core/intrusive/priorities.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

#include <memory>

namespace sway::render {

class RenderQueue {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  /**
   * @brief \~english Constructor class. Performs initialization of a new instance of the class. \~russian Конструктор
   * класса. Выполняет инициализацию нового экземпляра класса.
   */
  RenderQueue();

  /**
   * \~english
   * @brief Constructor class. Performs initialization of a new instance of the class.
   * @param[in] priority Queue priority.
   *
   * \~russian
   * @brief Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   * @param[in] priority Приоритет очереди.
   */
  RenderQueue(u32_t priority);

  DTOR(RenderQueue);

  /** @} */
#pragma endregion

  /**
   * \~english
   * @brief Adds a @ref RenderSubqueue to the group.
   * @param[in] subqueue Pointer to the object of the subqueue, which should be added to the container.
   *
   * \~russian
   * @brief Добавляет подочередь @ref RenderSubqueue в группу.
   * @param[in] subqueue Указатель на обьект класса подочереди, которой следует добавить в контейнер.
   *
   * \~
   * @sa removeSubqueue(const RenderSubqueueSharedPtr_t &)
   */
  void addSubqueue(const RenderSubqueueSharedPtr_t &subqueue);

  /**
   * \~english
   * @brief Removes a @ref RenderSubqueue from the group.
   * @param[in] subqueue Pointer to the object of the subqueue, which should be removed from the container.
   *
   * \~russian
   * @brief Удаляет подочередь @ref RenderSubqueue из группы.
   * @param[in] subqueue Указатель на обьект класса подочереди, которой следует удалить из контейнера.
   *
   * \~
   * @sa addSubqueue(const RenderSubqueueSharedPtr_t &)
   */
  void removeSubqueue(const RenderSubqueueSharedPtr_t &subqueue);

  /**
   * \~english
   * @brief Gets the collection of subqueues.
   * @param[in] group Group of subqueues.
   *
   * \~russian
   * @brief Получает коллекцию подочередей.
   * @param[in] group Группа подочереди.
   */
  auto getSubqueues(RenderSubqueueGroup group) -> RenderSubqueueSharedPtrVec_t &;

  /**
   * @brief \~english Sets the priority value. \~russian Устанавливает значение приоритета.
   *
   * @sa getPriority() const
   */
  void setPriority(u32_t priority) { priority_ = priority; }

  /**
   * \~english @brief \~english Get the priority value. \~russian Получает значение приоритета.
   *
   * @sa setPriority(u32_t)
   */
  [[nodiscard]]
  auto getPriority() const -> u32_t {
    return priority_;
  }

  struct PriorityInDescendingOrder {
    bool operator()(const RenderQueueSharedPtr_t &lhs, const RenderQueueSharedPtr_t &rhs) const {
      return lhs->getPriority() > rhs->getPriority();
    }
  };

private:
  u32_t priority_;  //!< \~english Priority value. \~russian Приоритет очереди.
  RenderSubqueueContainer_t subqueues_[RENDER_SUBQUEUE_GROUP_COUNT]; /*!< \~english Container of subqueues.
    \~russian Контейнер подочередей. */
};

}  // namespace sway::render

#endif  // SWAY_RENDER_RENDERQUEUE_HPP
