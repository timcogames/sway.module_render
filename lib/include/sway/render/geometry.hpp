#ifndef SWAY_RENDER_GEOMETRY_HPP
#define SWAY_RENDER_GEOMETRY_HPP

#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/geometryvertexdata.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/shape.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct UVData {
  std::vector<math::vec2f_t> uv;
};

class VertexComponent {
public:
  static auto hasPosition() -> bool { return false; }

  static auto hasColor() -> bool { return false; }

  static auto hasTexCoord() -> bool { return false; }
};

struct Position {
  f32_t x, y, z;
};

// template <class TVertexComponent>
// class PositionVertexComponent : public TVertexComponent {
class PositionVertexComponent : public VertexComponent {
public:
  static auto hasPosition() -> bool { return true; }

  [[nodiscard]] auto getPosition() const -> Position { return position_; }

private:
  Position position_;
};

struct Color {
  f32_t r, g, b, a;
};

// template <class TVertexComponent>
// class ColorVertexComponent : public TVertexComponent {
class ColorVertexComponent {
public:
  static auto hasColor() -> bool { return true; }

  [[nodiscard]] auto getColor() const -> Color { return color_; }

private:
  Color color_;
};

struct TexCoord {
  f32_t u, v;
};

// template <class TVertexComponent>
// class TextCoordVertexComponent : public TVertexComponent {
class TextCoordVertexComponent {
public:
  static auto hasTexCoord() -> bool { return true; }

  [[nodiscard]] auto getTexCoord() const -> TexCoord { return coord_; }

private:
  TexCoord coord_;
};

class CustomVertex : public PositionVertexComponent {
public:
};

class Geometry {
public:
  Geometry(std::shared_ptr<gapi::IdGenerator> idgen, EffectRef_t effect, bool indexed);

  ~Geometry() = default;

  void create(std::shared_ptr<procedurals::Shape> prim);

  void updateUV(std::vector<UVData> uvdata, const math::size2i_t &segments);

  auto getVertexAttribLayout() -> gapi::VertexAttribLayoutPtr_t { return vtxAttribLayout_; }

  auto getVtxArray() -> gapi::VertexArrayPtr_t { return vtxArray_; }

  /**
   * @brief Получает указатель на объект вершинного буфера.
   *
   * @sa getIndexBuffer()
   */
  auto getVertexBuffer() -> gapi::BufferRef_t { return vtxBuffer_; }

  /**
   * @brief Получает указатель на объект индексного буфера.
   *
   * @sa getVertexBuffer()
   */
  auto getIndexBuffer() -> gapi::BufferRef_t { return idxBuffer_; }

  [[nodiscard]] auto getTopology() const -> gapi::TopologyType;

  void bind();

  void unbind();

private:
  GeometryCreateInfo info_;
  std::shared_ptr<gapi::IdGenerator> idGenerator_;
  VertexAttribMap_t vtxAttribs_;
  gapi::VertexAttribLayoutPtr_t vtxAttribLayout_;
  gapi::VertexArrayPtr_t vtxArray_;
  gapi::BufferRef_t vtxBuffer_;  // Объект буфера вершин.
  gapi::BufferRef_t idxBuffer_;  // Объект буфера индексов.
  EffectRef_t effect_;
  bool indexed_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMETRY_HPP
