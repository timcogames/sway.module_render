#ifndef SWAY_RENDER_RENDERSUBSYSTEM_HPP
#define SWAY_RENDER_RENDERSUBSYSTEM_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/geom/geombuilder.hpp>
#include <sway/render/ppe/fullscreenquadrilateral.hpp>
#include <sway/render/ppe/postprocessing.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderpass.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/renderstages.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

#include <array>  // std::array
#include <memory>  // std::shared_ptr
#include <stack>  // std::stack
#include <vector>  // std::vector

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderSubsystem : public core::foundation::Subsystem {
  DECLARE_CLASS_METADATA(RenderSubsystem, core::foundation::Subsystem);
  DECLARE_CLASS_POINTER_ALIASES(RenderSubsystem)

public:
#pragma region "Ctors/Dtor"

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] context Контекст подсистемы.
   */
  RenderSubsystem(core::Plugin *plug, core::foundation::Context::Ptr_t context);

  /**
   * @brief Деструктор класса. Освобождает захваченные ресурсы.
   */
  virtual ~RenderSubsystem();

#pragma endregion

  void createPostProcessing(RenderSubqueue::SharedPtr_t subqueue,
      Material::SharedPtr_t material);  // -> FullscreenQuadrilateral::SharedPtr_t;

  /**
   * @brief Создает новую очередь и добавляет её в контейнер.
   *
   * @param[in] priority Приоритет очереди.
   * @return Умный указатель на объект класса очереди.
   */
  auto createQueue(u32_t priority) -> RenderQueue::SharedPtr_t;

  /**
   * @brief Получает очередь по индексу.
   *
   * @param[in] idx Индекс очереди.
   * @return Умный указатель на объект класса очереди.
   */
  auto getQueueByIdx(u32_t idx) -> RenderQueue::SharedPtr_t { return queues_[idx]; }

  auto getQueueByPriority(u32_t priority) -> RenderQueue::SharedPtr_t;

  /**
   * @brief Получает все очереди.
   */
  auto getQueues() -> RenderQueueSharedPtrVec_t { return queues_; }

  /**
   * @brief Сортирует очереди по приоритету.
   */
  void sortQueues();

  /**
   * @brief Метод отрисовки.
   */
  void render();

#pragma region "Override Subsystem methods"

  MTHD_OVERRIDE(auto initialize() -> bool);

  MTHD_OVERRIDE(void tick(f32_t dtm)) {}

  MTHD_OVERRIDE(void shutdown()) {}

#pragma endregion

  auto getIdGenerator() -> gapi::IdGeneratorPtr_t { return idGenerator_; }

  auto getGeomBuilder() -> GeomBuilder::SharedPtr_t { return geomBuilder_; }

public:
  void renderSubqueues_(
      RenderQueue::SharedPtr_t queue, RenderSubqueueGroup group, u32_t stage, RenderState::SharedPtr_t state);

  gapi::CapabilityPtr_t capability_;
  gapi::ViewportPtr_t viewport_;
  PostProcessing::SharedPtr_t ppe_;
  RenderQueueSharedPtrVec_t queues_;
  gapi::IdGeneratorPtr_t idGenerator_;
  GeomBuilder::SharedPtr_t geomBuilder_;
  FullscreenQuadrilateral::SharedPtr_t fullscreenQuad_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERSUBSYSTEM_HPP
