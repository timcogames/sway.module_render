#ifndef SWAY_RENDER_RENDERSUBQUEUE_HPP
#define SWAY_RENDER_RENDERSUBQUEUE_HPP

#include <sway/gapi.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/pipeline/rendercommandhandler.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderSubqueue {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] group Группа подочереди.
   */
  RenderSubqueue(RenderSubqueueGroup group = RenderSubqueueGroup::OPAQUE);

  ~RenderSubqueue() = default;

  void initialize();

  /**
   * @brief Добавляет отрисовываемый объект.
   *
   * @param[in] geometry Отрисовываемый объект.
   */
  // void addGeometry(GeometryRef_t geometry);

  void post(pipeline::ForwardRenderCommand command);

  /**
   * @brief Метод отрисовки.
   */
  void render();

  /**
   * @brief Устанавливает группу подочереди.
   *
   * @param[in] group Группа подочереди.
   */
  void setGroup(RenderSubqueueGroup group) { group_ = group; }

  /**
   * @brief Получает группу подочереди.
   */
  [[nodiscard]] auto getGroup() const -> RenderSubqueueGroup { return group_; }

private:
  gapi::DrawCallRef_t drawCall_;
  gapi::StateRef_t state_;
  std::vector<pipeline::ForwardRenderCommand> commands_;
  RenderSubqueueGroup group_;  // Группа подочереди.
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERSUBQUEUE_HPP
