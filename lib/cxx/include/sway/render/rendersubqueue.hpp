#ifndef SWAY_RENDER_RENDERSUBQUEUE_HPP
#define SWAY_RENDER_RENDERSUBQUEUE_HPP

#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/renderstate.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

#include <memory>

namespace sway::render {

class RenderSubqueue {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  /**
   * \~english
   * @brief Constructor class. Initializes a new instance of the class.
   * @param[in] group Subqueue group.
   *
   * \~russian
   * @brief Конструктор класса.Выполняет инициализацию нового экземпляра класса.
   * @param[in] group Группа подочереди.
   */
  RenderSubqueue(RenderSubqueueGroup group = RenderSubqueueGroup::OPAQUE);

  DTOR_DEFAULT(RenderSubqueue);

  /** @} */
#pragma endregion

  void initialize();

  void post(pipeline::ForwardRenderCommand cmd);

  /**
   * @brief \~english Method for rendering. \~russian Метод отрисовки.
   */
  void render(u32_t stage, gapi::typedefs::StateContextPtr_t state);

  /**
   * \~english
   * @brief Sets the group of the subqueue.
   * @param[in] group Subqueue group.
   *
   * \~russian
   * @brief Устанавливает группу подочереди.
   * @param[in] group Группа подочереди.
   */
  void setGroup(RenderSubqueueGroup group) { group_ = group; }

  /**
   * @brief \~english Gets the group of the subqueue. \~russian Получает группу подочереди.
   */
  [[nodiscard]] auto getGroup() const -> RenderSubqueueGroup { return group_; }

  [[nodiscard]] auto getCommands() -> std::vector<pipeline::ForwardRenderCommand> { return commands_; }

private:
  void renderItem_(pipeline::ForwardRenderCommand cmd, gapi::typedefs::StateContextPtr_t state);

  std::vector<pipeline::ForwardRenderCommand> commands_;
  std::shared_ptr<math::MatrixStack> matrixStack_;
  RenderSubqueueGroup group_;  //!< \~english Subqueue group. \~russian Группа подочереди.
};

}  // namespace sway::render

#endif  // SWAY_RENDER_RENDERSUBQUEUE_HPP
