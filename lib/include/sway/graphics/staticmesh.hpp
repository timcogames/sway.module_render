#ifndef SWAY_GRAPHICS_STATICMESH_HPP
#define SWAY_GRAPHICS_STATICMESH_HPP

#include <sway/graphics/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class StaticMesh {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  StaticMesh(RenderSubqueueRef_t subqueue, VertexDataRef_t vtxdata, MaterialRef_t material);

  /**
   * @brief Деструктор класса. Освобождает захваченные ресурсы.
   */
  ~StaticMesh() = default;

private:
  VertexDataRef_t vtxdata_;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_STATICMESH_HPP
