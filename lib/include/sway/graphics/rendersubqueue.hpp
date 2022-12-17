#ifndef SWAY_GRAPHICS_RENDERSUBQUEUE_HPP
#define SWAY_GRAPHICS_RENDERSUBQUEUE_HPP

#include <sway/graphics/prereqs.hpp>
#include <sway/graphics/rendersubqueuegroups.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

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

  /**
   * @brief Добавляет отрисовываемый объект.
   *
   * @param[in] drawable Отрисовываемый объект.
   */
  void addDrawable(DrawableRef_t drawable);

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
  DrawableRefVec_t drawables_;
  RenderSubqueueGroup group_;  // Группа подочереди.
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_RENDERSUBQUEUE_HPP
