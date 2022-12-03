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
   * @param[in] group Группа подочереди.
   */
  RenderSubqueue(RenderSubqueueGroup_t group = RenderSubqueueGroup_t::kOpaque);

  ~RenderSubqueue() = default;

  /**
   * @brief Добавляет отрисовываемый объект.
   * @param[in] drawable Отрисовываемый объект.
   */
  void addDrawable(DrawableRef_t drawable);

  /**
   * @brief Метод отрисовки.
   */
  void render();

  /**
   * @brief Устанавливает группу подочереди.
   * @param[in] group Группа подочереди.
   */
  void setGroup(RenderSubqueueGroup_t group) { group_ = group; }

  /**
   * @brief Получает группу подочереди.
   */
  auto getGroup() const -> RenderSubqueueGroup_t { return group_; }

private:
  gapi::DrawCallRef_t drawCall_;
  DrawableRefVec_t drawables_;
  RenderSubqueueGroup_t group_;  // Группа подочереди.
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_RENDERSUBQUEUE_HPP
