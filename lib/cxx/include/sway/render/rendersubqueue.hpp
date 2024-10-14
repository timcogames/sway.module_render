#ifndef SWAY_RENDER_RENDERSUBQUEUE_HPP
#define SWAY_RENDER_RENDERSUBQUEUE_HPP

#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/pipeline/rendercommandhandler.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderstate.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class RenderSubqueue {
  DECLARE_PTR_ALIASES(RenderSubqueue)
  DECLARE_PTR_VECTOR(RenderSubqueue, SharedPtr)

public:
#pragma region "Ctors/Dtor"

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] group Группа подочереди.
   */
  RenderSubqueue(RenderSubqueueGroup group = RenderSubqueueGroup::OPAQUE);

  ~RenderSubqueue() = default;

#pragma endregion

  void initialize();

  void post(pipeline::ForwardRenderCommand cmd);

  /**
   * @brief Метод отрисовки.
   */
  void render(u32_t stage, gapi::StateContextPtr_t state);

  /**
   * @brief Устанавливает группу подочереди.
   *
   * @param[in] group Группа подочереди.
   */
  void setGroup(RenderSubqueueGroup group) { group_ = group; }

  /**
   * @brief Получает группу подочереди.
   */
  [[nodiscard]]
  auto getGroup() const -> RenderSubqueueGroup {
    return group_;
  }

  [[nodiscard]]
  auto getCommands() -> std::vector<pipeline::ForwardRenderCommand> {
    return commands_;
  }

private:
  void renderItem_(pipeline::ForwardRenderCommand cmd, gapi::StateContextPtr_t state);

  gapi::DrawCallPtr_t drawCall_;
  std::vector<pipeline::ForwardRenderCommand> commands_;
  std::shared_ptr<math::MatrixStack> matrixStack_;
  RenderSubqueueGroup group_;  // Группа подочереди.
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERSUBQUEUE_HPP
