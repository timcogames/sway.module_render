#ifndef SWAY_GRAPHICS_PRIMITIVES_QUAD_HPP
#define SWAY_GRAPHICS_PRIMITIVES_QUAD_HPP

#include <sway/graphics/prereqs.hpp>
#include <sway/graphics/vertexdata.hpp>
#include <sway/math.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)
NAMESPACE_BEGIN(primitives)

class Quad : public VertexData {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  Quad(f32_t width, f32_t height);

  /**
   * @brief Деструктор класса. Освобождает захваченные ресурсы.
   */
  virtual ~Quad() = default;
};

NAMESPACE_END(primitives)
NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_PRIMITIVES_QUAD_HPP
