#ifndef SWAY_GRAPHICS_DRAWABLE_HPP
#define SWAY_GRAPHICS_DRAWABLE_HPP

#include <sway/graphics/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Drawable {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  Drawable(MaterialRef_t material, bool indexed);

  ~Drawable() = default;

  void create(VertexDataRef_t vertexData, const gapi::BufferCreateInfoSet &infoSet);

  /**
   * @brief Получает указатель на объект вершинного буфера.
   * @sa getIBO()
   */
  auto getVBO() -> gapi::BufferRef_t { return vbo_; }

  /**
   * @brief Получает указатель на объект индексного буфера.
   * @sa getVBO()
   */
  auto getIBO() -> gapi::BufferRef_t { return ibo_; }

  auto getVertexLayout() -> gapi::VertexLayoutRef_t { return vlayout_; }

  auto getMaterial() -> MaterialRef_t { return material_; }

private:
  gapi::BufferRef_t vbo_;  // Объект буфера вершин.
  gapi::BufferRef_t ibo_;  // Объект буфера индексов.
  gapi::VertexLayoutRef_t vlayout_;
  VertexDataRef_t vertexData_;
  MaterialRef_t material_;
  bool indexed_;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif
