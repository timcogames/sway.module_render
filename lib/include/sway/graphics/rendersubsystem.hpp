#ifndef SWAY_GRAPHICS_RENDERSUBSYSTEM_HPP
#define SWAY_GRAPHICS_RENDERSUBSYSTEM_HPP

#include <sway/core/intrusive/priorities.hpp>
#include <sway/graphics/prereqs.hpp>
#include <sway/graphics/rendersubqueuegroups.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

namespace global {
auto getGapiFunctionSet() -> gapi::ConcreatePluginFunctionSet *;
}  // namespace global

class RenderSubsystem : public core::foundation::Subsystem {
public:
  DECLARE_CLASS_METADATA(RenderSubsystem, core::foundation::Subsystem);

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] context Контекст подсистемы.
   */
  RenderSubsystem(const std::string &plugname, core::foundation::Context *context);

  /**
   * @brief Деструктор класса. Освобождает захваченные ресурсы.
   */
  virtual ~RenderSubsystem();

  /**
   * @brief Создает новую очередь и добавляет её в контейнер.
   *
   * @param[in] priority Приоритет очереди.
   * @return Умный указатель на объект класса очереди.
   */
  auto createQueue(u32_t priority = core::intrusive::Priority_Normal) -> RenderQueueRef_t;

  /**
   * @brief Получает очередь по индексу.
   *
   * @param[in] index Индекс очереди.
   * @return Умный указатель на объект класса очереди.
   */
  auto getQueueByIdx(u32_t index) -> RenderQueueRef_t { return queues_[index]; }

  /**
   * @brief Получает все очереди.
   */
  auto getQueues() -> RenderQueueRefVector_t { return queues_; }

  /**
   * @brief Сортирует очереди по приоритету.
   */
  void sortQueues();

  /**
   * @brief Метод отрисовки.
   */
  void render();

  MTHD_OVERRIDE(bool initialize()) { return true; }

  MTHD_OVERRIDE(void tick(float timestep)) {}

  MTHD_OVERRIDE(void shutdown()) {}

private:
  void renderSubqueues_(RenderQueueRef_t queue, RenderSubqueueGroup group);

  gapi::CapabilityRef_t capability_;
  RenderQueueRefVector_t queues_;  // Контейнер очередей.
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_RENDERSUBSYSTEM_HPP
