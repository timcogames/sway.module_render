#ifndef SWAY_RENDER_GEOMETRY_HPP
#define SWAY_RENDER_GEOMETRY_HPP

#include <sway/gapi.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/geometryvertexdata.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/shape.hpp>

#include <array>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class VertexComponent {
public:
  static auto hasPosition() -> bool { return false; }

  static auto hasColor() -> bool { return false; }

  static auto hasTexCoord() -> bool { return false; }
};

// template <class TVertexComponent>
// class PositionVertexComponent : public TVertexComponent {
class PositionVertexComponent : public VertexComponent {
public:
  static auto hasPosition() -> bool { return true; }

  [[nodiscard]]
  auto getPosition() const -> math::vec3f_t {
    return position_;
  }

private:
  math::vec3f_t position_;
};

// template <class TVertexComponent>
// class ColorVertexComponent : public TVertexComponent {
class ColorVertexComponent {
public:
  static auto hasColor() -> bool { return true; }

  [[nodiscard]]
  auto getColor() const -> math::vec4f_t {
    return color_;
  }

private:
  math::vec4f_t color_;
};

// template <class TVertexComponent>
// class TexCoordVertexComponent : public TVertexComponent {
class TexCoordVertexComponent {
public:
  static auto hasTexCoord() -> bool { return true; }

  [[nodiscard]]
  auto getTexCoord() const -> math::vec2f_t {
    return uv_;
  }

private:
  math::vec2f_t uv_;
};

class CustomVertex : public PositionVertexComponent {
public:
};

#define QUAD_TEXCOORD_SIZE 4

struct UVData {
  std::vector<math::vec2f_t> uv;
};

class Geometry {
public:
  Geometry(std::shared_ptr<gapi::IdGenerator> idgen, EffectRef_t effect, bool indexed);

  ~Geometry() = default;

  void create(std::shared_ptr<procedurals::Shape> prim);

  void updateUV(std::vector<UVData> uvdata, const math::size2i_t &segments);

  void setUV(int index, std::array<math::vec2f_t, 4> coords);

  auto getVertexAttribLayout() -> gapi::VertexAttribLayoutPtr_t { return vtxAttribLayout_; }

  auto getVtxArray() -> gapi::VertexArrayPtr_t { return vtxArray_; }

  auto getBufferSet() -> gapi::BufferSet { return bufset_; }

  [[nodiscard]]
  auto getTopology() const -> gapi::TopologyType;

  void bind();

  void unbind();

private:
  GeometryCreateInfo info_;
  std::shared_ptr<gapi::IdGenerator> idGenerator_;
  VertexAttribMap_t vtxAttribs_;
  gapi::VertexAttribLayoutPtr_t vtxAttribLayout_;
  gapi::VertexArrayPtr_t vtxArray_;
  gapi::BufferSet bufset_{nullptr, nullptr};
  EffectRef_t effect_;
  bool indexed_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMETRY_HPP
