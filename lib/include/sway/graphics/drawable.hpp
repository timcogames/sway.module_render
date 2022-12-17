#ifndef SWAY_GRAPHICS_DRAWABLE_HPP
#define SWAY_GRAPHICS_DRAWABLE_HPP

#include <sway/graphics/geometrycreateinfo.hpp>
#include <sway/graphics/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Drawable {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  Drawable(const GeometryCreateInfo &info, MaterialRef_t material, bool indexed);

  ~Drawable() = default;

  void create(VertexDataRef_t vertexData);

  /**
   * @brief Получает указатель на объект вершинного буфера.
   *
   * @sa getIBO()
   */
  auto getVBO() -> gapi::BufferRef_t { return vbuffer_; }

  /**
   * @brief Получает указатель на объект индексного буфера.
   *
   * @sa getVBO()
   */
  auto getIBO() -> gapi::BufferRef_t { return ibuffer_; }

  auto getVertexLayout() -> gapi::VertexAttribLayoutPtr_t { return vlayout_; }

  auto getMaterial() -> MaterialRef_t { return material_; }

  [[nodiscard]] auto getTopology() const -> gapi::TopologyType;

private:
  GeometryCreateInfo geometryCreateInfo_;
  std::shared_ptr<gapi::IdGenerator> idGenerator_;
  gapi::BufferRef_t vbuffer_;  // Объект буфера вершин.
  gapi::BufferRef_t ibuffer_;  // Объект буфера индексов.
  gapi::VertexAttribLayoutPtr_t vlayout_;
  VertexDataRef_t vertexData_;
  MaterialRef_t material_;
  bool indexed_;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif
