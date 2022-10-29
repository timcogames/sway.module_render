#ifndef SWAY_GRAPHICS_STATICMESH_HPP
#define SWAY_GRAPHICS_STATICMESH_HPP

#include <sway/graphics/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class StaticMesh {
public:
  /*!
   * \brief
   *    Конструктор класса.
   *    Выполняет инициализацию нового экземпляра класса.
   */
  StaticMesh(RenderSubqueueRef_t subqueue, MaterialRef_t material);

  /*!
   * \brief
   *    Деструктор класса.
   *    Освобождает захваченные ресурсы.
   */
  ~StaticMesh();

private:
  VertexDataRef_t _vertexData;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif
