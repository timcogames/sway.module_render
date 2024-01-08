#ifndef SWAY_RENDER_RENDERSUBSYSTEM_HPP
#define SWAY_RENDER_RENDERSUBSYSTEM_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderpass.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

#include <array>  // std::array
#include <memory>  // std::shared_ptr
#include <stack>  // std::stack
#include <vector>  // std::vector

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

enum class RenderStage : u32_t { DEPTH = 0, COLOR = 1, STENCIL = 2, MAX_STAGE = 3 };

class RenderSubsystem : public core::foundation::Subsystem {
public:
  DECLARE_CLASS_METADATA(RenderSubsystem, core::foundation::Subsystem);

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] context Контекст подсистемы.
   */
  RenderSubsystem(core::Plugin *plug, core::foundation::Context *context);

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
  auto createQueue(u32_t priority) -> RenderQueueRef_t;

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

  // clang-format off
  MTHD_OVERRIDE(auto initialize() -> bool);  // clang-format on

  MTHD_OVERRIDE(void tick(float timestep)) {}

  MTHD_OVERRIDE(void shutdown()) {}

  auto getIdGenerator() -> std::shared_ptr<gapi::IdGenerator> { return idGenerator_; }

private:
  void renderSubqueues_(
      RenderQueueRef_t queue, RenderSubqueueGroup group, u32_t stage, std::shared_ptr<RenderState> state);

  std::shared_ptr<gapi::Capability> capability_;
  std::array<std::shared_ptr<RenderPass>, core::detail::toUnderlying(RenderStage::MAX_STAGE)> passes_{};
  RenderQueueRefVector_t queues_;  // Контейнер очередей.
  std::shared_ptr<gapi::IdGenerator> idGenerator_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERSUBSYSTEM_HPP
