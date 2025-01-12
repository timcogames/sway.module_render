#ifndef SWAY_RENDER_RENDERSUBSYSTEM_HPP
#define SWAY_RENDER_RENDERSUBSYSTEM_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/_typedefs.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/geom/geombuilder.hpp>
#include <sway/render/ppe/postprocessing.hpp>
#include <sway/render/ppe/screenquad.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

namespace sway::render {

class RenderSubsystem : public core::Subsystem {
  DECLARE_CLASS_METADATA(RenderSubsystem, core::Subsystem);

public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  /**
   * \~english
   * @brief Constructor class. Performs initialization of a new instance of the class.
   * @param[in] ctx Context of the subsystem.
   *
   * \~russian
   * @brief Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   * @param[in] ctx Контекст подсистемы.
   */
  RenderSubsystem(core::Plugin *plug, core::typedefs::ContextPtr_t context);

  DTOR_VIRTUAL(RenderSubsystem);

  /** @} */
#pragma endregion

  void setGraphicsApiContext(global::GapiPluginFunctionSet *pluginFuncs);

  void createPostProcessing(RenderSubqueueSharedPtr_t subqueue, core::Dictionary glob);

  /**
   * \~english
   * @brief Gets the queue by index.
   * @param[in] idx Queue index.
   * @return Smart pointer to the queue object.
   *
   * \~russian
   * @brief Получает очередь по индексу.
   * @param[in] idx Индекс очереди.
   * @return Умный указатель на объект класса очереди.
   */
  auto getQueueByIdx(u32_t idx) -> RenderQueueSharedPtr_t { return queues_[idx]; }

  auto getQueueByPriority(u32_t priority) -> RenderQueueSharedPtr_t;

  /**
   * \~english
   * @brief Creates a new queue and adds it to the container.
   * @param[in] priority Queue priority.
   * @return Smart pointer to the queue object.
   *
   * \~russian
   * @brief Создает новую очередь и добавляет её в контейнер.
   * @param[in] priority Приоритет очереди.
   * @return Умный указатель на объект класса очереди.
   */
  auto createQueue(u32_t priority) -> RenderQueueSharedPtr_t;

  void createQueuePass(const std::string &name, i32_t idx);

  /**
   * @brief \~english Gets all queues. \~russian Получает все очереди.
   */
  auto getQueues() -> RenderQueueSharedPtrVec_t { return queues_; }

  /**
   * @brief \~english Sorts queues by priority. \~russian Сортирует очереди по приоритету.
   */
  void sortQueues();

  /**
   * @brief \~english Method for rendering. \~russian Метод отрисовки.
   */
  void render();

#pragma region "Overridden Subsystem methods"

  MTHD_OVERRIDE(auto initialize() -> bool);

  MTHD_OVERRIDE(void tick(f32_t dtm)) {}

  MTHD_OVERRIDE(void shutdown()) {}

#pragma endregion

  auto getIdGenerator(i32_t idx) const { return idGenerator_[idx]; }

  auto getGeomBuilder() -> GeomBuilderTypedefs::SharedPtr_t { return geomBuilder_; }

public:
  void renderSubqueues_(
      RenderQueueSharedPtr_t queue, RenderSubqueueGroup group, u32_t stage, RenderStateSharedPtr_t state);

  global::GapiPluginFunctionSet *deviceContext_;

  gapi::StateEnableable<gapi::RasterizerDescriptor> *rasterizer_;
  RenderStateSharedPtr_t renderState_;
  gapi::typedefs::ViewportPtr_t viewport_;
  PostProcessingSharedPtr_t ppe_;
  RenderQueueSharedPtrVec_t queues_;
  std::array<gapi::typedefs::IdGeneratorPtr_t, 3> idGenerator_;
  GeomBuilderTypedefs::SharedPtr_t geomBuilder_;
  ScreenQuadSharedPtr_t fullscreenQuad_;

  experience::RenderModuleTypedefs::UniquePtr_t renderModule_;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_RENDERSUBSYSTEM_HPP
