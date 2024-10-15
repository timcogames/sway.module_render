#ifndef SWAY_RENDER_RENDERSUBSYSTEM_HPP
#define SWAY_RENDER_RENDERSUBSYSTEM_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/geom/geombuilder.hpp>
#include <sway/render/ppe/postprocessing.hpp>
#include <sway/render/ppe/screenquad.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueuegroups.hpp>
#include <sway/render/temp/pipeline.hpp>
#include <sway/render/temp/renderer.hpp>

#include <array>  // std::array
#include <stack>  // std::stack
#include <vector>  // std::vector

NS_BEGIN_SWAY()
NS_BEGIN(render)

class RenderSubsystem : public core::foundation::Subsystem {
  DECLARE_CLASS_METADATA(RenderSubsystem, core::foundation::Subsystem);
  DECLARE_PTR_ALIASES(RenderSubsystem)

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

  void createPostProcessing(RenderSubqueue::SharedPtr_t subqueue, core::misc::Dictionary glob);

  /**
   * @brief Получает очередь по индексу.
   *
   * @param[in] idx Индекс очереди.
   * @return Умный указатель на объект класса очереди.
   */
  auto getQueueByIdx(u32_t idx) -> RenderQueue::SharedPtr_t { return queues_[idx]; }

  auto getQueueByPriority(u32_t priority) -> RenderQueue::SharedPtr_t;

  /**
   * @brief Создает новую очередь и добавляет её в контейнер.
   *
   * @param[in] priority Приоритет очереди.
   * @return Умный указатель на объект класса очереди.
   */
  auto createQueue(u32_t priority) -> RenderQueue::SharedPtr_t;

  void createQueuePass(const std::string &name, i32_t idx);

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

  auto getIdGenerator(i32_t idx) const { return idGenerator_[idx]; }

  auto getGeomBuilder() -> GeomBuilder::SharedPtr_t { return geomBuilder_; }

public:
  void renderSubqueues_(
      RenderQueue::SharedPtr_t queue, RenderSubqueueGroup group, u32_t stage, RenderState::SharedPtr_t state);

  gapi::CapabilityPtr_t capability_;
  gapi::StateEnableable<gapi::RasterizerDescriptor> *rasterizer_;
  RenderState::SharedPtr_t renderState_;
  gapi::ViewportPtr_t viewport_;
  PostProcessing::SharedPtr_t ppe_;
  RenderQueueSharedPtrVec_t queues_;
  std::array<gapi::IdGenerator::Ptr_t, 3> idGenerator_;
  GeomBuilder::SharedPtr_t geomBuilder_;
  ScreenQuad::SharedPtr_t fullscreenQuad_;

  void addRenderer(Renderer::UniquePtr_t renderer) { availRenderers_.push_back(std::move(renderer)); }

  auto getRenderer_(u32_t type) -> Renderer::UniquePtrVec_t::iterator {
    return std::find_if(availRenderers_.begin(), availRenderers_.end(),
        [&](Renderer::UniquePtr_t &renderer) { return renderer->type() == type; });
  }

  void setActiveRenderer(u32_t type) { activeRenderer_ = std::move(*getRenderer_(type)); }

  auto getActiveRenderer() -> Renderer::UniquePtr_t & { return activeRenderer_; }

  Renderer::UniquePtrVec_t availRenderers_;
  Renderer::UniquePtr_t activeRenderer_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERSUBSYSTEM_HPP
