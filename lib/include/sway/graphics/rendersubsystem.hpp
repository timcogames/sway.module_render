#ifndef SWAY_GRAPHICS_RENDERSUBSYSTEM_HPP
#define SWAY_GRAPHICS_RENDERSUBSYSTEM_HPP

#include <sway/core/intrusive/priorities.hpp>
#include <sway/graphics/prereqs.hpp>
#include <sway/graphics/rendersubqueuegroups.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

namespace global {
gapi::ConcreatePluginFunctionSet *getGapiFunctionSet();
}  // namespace global

class RenderSubsystem : public core::foundation::Object {
  // DECLARE_OBJECT(RenderSubsystem, core::foundation::Object);

public:
  /*!
   * \brief
   *    Конструктор класса.
   *    Выполняет инициализацию нового экземпляра класса.
   *
   * \param[in] context
   *    Контекст подсистемы.
   */
  RenderSubsystem(const std::string &plugname, core::foundation::Context *context);

  /*!
   * \brief
   *    Деструктор класса.
   *    Освобождает захваченные ресурсы.
   */
  virtual ~RenderSubsystem();

  /*!
   * \brief
   *    Создает новую очередь и добавляет её в контейнер.
   *
   * \param[in] priority
   *    Приоритет очереди.
   *
   * \return
   *    Умный указатель на объект класса очереди.
   */
  RenderQueueRef_t createQueue(u32_t priority = core::intrusive::kPriority_Normal);

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
  void renderSubqueues_(RenderQueueRef_t queue, RenderSubqueueGroup_t group);

  gapi::CapabilityRef_t capability_;
  RenderQueueRefVector_t queues_; /*!< Контейнер очередей. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif
