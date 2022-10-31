#ifndef SWAY_GRAPHICS_DRAWABLE_HPP
#define SWAY_GRAPHICS_DRAWABLE_HPP

#include <sway/graphics/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Drawable {
public:
  /*!
   * \brief
   *    Конструктор класса.
   *    Выполняет инициализацию нового экземпляра класса.
   */
  Drawable(MaterialRef_t material, bool indexed);

  /*!
   * \brief
   *    Деструктор класса.
   *    Освобождает захваченные ресурсы.
   */
  ~Drawable();

  void create(VertexDataRef_t vertexData, const gapi::BufferCreateInfoSet &infoSet);

  /*!
   * \brief
   *   Получает указатель на объект вершинного буфера.
   *
   * \sa
   *   getIBO()
   */
  gapi::BufferRef_t getVBO();

  /*!
   * \brief
   *   Получает указатель на объект индексного буфера.
   *
   * \sa
   *   getVBO()
   */
  gapi::BufferRef_t getIBO();

  gapi::VertexLayoutRef_t getVertexLayout();

  MaterialRef_t getMaterial();

private:
  gapi::BufferRef_t vbo_; /*!< Объект буфера вершин. */
  gapi::BufferRef_t ibo_; /*!< Объект буфера индексов. */
  gapi::VertexLayoutRef_t vlayout_;
  VertexDataRef_t vertexData_;
  MaterialRef_t material_;
  bool indexed_;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif
