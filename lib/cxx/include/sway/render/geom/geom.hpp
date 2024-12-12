#ifndef SWAY_RENDER_GEOM_HPP
#define SWAY_RENDER_GEOM_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/effect/effect.hpp>
#include <sway/render/geom/geomcreateinfo.hpp>
#include <sway/render/geom/geomvertexattribbase.hpp>
#include <sway/render/global.hpp>
#include <sway/render/prereqs.hpp>

#include <algorithm>
#include <array>
#include <optional>

NS_BEGIN_SWAY()
NS_BEGIN(render)

#define QUAD_TEXCOORD_SIZE2 4

class VertexBuffer {
private:
  u32_t vboUid_;  ///< Unique id of the vertex buffer object
};

class VertexArray {
public:
  void create() { vbo_ = std::make_unique<VertexBuffer>(); }

private:
  std::unique_ptr<VertexBuffer> vbo_;
  u32_t vaoUid_;  ///< Unique id of the vertex array object
};

class IndexBuffer {
private:
  u32_t iaoUid_;  ///< Unique id of the index array object
  std::vector<u32_t> indices_;
};

struct UVData2 {
  std::vector<math::vec2f_t> uv;
};

class Geom : public core::foundation::Uniqueable<std::string> {
public:
#pragma region "Ctors/Dtor"

  Geom(global::GapiPluginFunctionSet *plug, GeomBuilderPtr_t builder);

  DTOR_VIRTUAL(Geom);

#pragma endregion

  template <class OBJ>
  void call(std::function<void(OBJ)> callback);

  MTHD_VIRTUAL(void create(
      const GeomCreateInfo &info, EffectTypedefs::Ptr_t effect, GeomVertexAttribSharedPtrMap_t attribs));

#pragma region "Binding/Unbinding"

  MTHD_VIRTUAL(void bind());

  MTHD_VIRTUAL(void unbind());

#pragma endregion

  auto getBuffer(int idx) -> std::optional<gapi::BufferPtr_t> { return buffers_[idx]; }

  void updateUV(std::vector<UVData2> uvdata);

  void setUV(int index, std::array<math::vec2f_t, 4> coords);

protected:
  global::GapiPluginFunctionSet *gapiPlugin_;
  GeomBuilderPtr_t builder_;

private:
  gapi::VertexArrayPtr_t vao_;
  gapi::VertexAttribLayoutPtr_t attribLayout_;
  GeomVertexAttribSharedPtrMap_t attribs_;
  std::array<std::optional<gapi::BufferPtr_t>, Constants::MAX_IDX_BUFFERS> buffers_{};
};

NS_END()  // namespace render
NS_END()  // namespace sway

#include <sway/render/geom/geom.inl>

#endif  // SWAY_RENDER_GEOM_HPP
