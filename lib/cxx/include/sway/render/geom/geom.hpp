#ifndef SWAY_RENDER_GEOM_HPP
#define SWAY_RENDER_GEOM_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect.hpp>
#include <sway/render/geom/geomvertexattribbase.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/global.hpp>
#include <sway/render/prereqs.hpp>

#include <algorithm>
#include <array>
#include <optional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

#define QUAD_TEXCOORD_SIZE2 4

struct UVData2 {
  std::vector<math::vec2f_t> uv;
};

class Geom : public core::foundation::Uniqueable<std::string> {
  DECLARE_CLASS_POINTER_ALIASES(Geom)

public:
#pragma region "Ctors/Dtor"

  Geom(global::GapiPluginFunctionSet *plug, GeomBuilderPtr_t builder);

  virtual ~Geom();

#pragma endregion

  template <class TObject>
  void call(std::function<void(TObject)> callback);

  MTHD_VIRTUAL(void create(const GeometryCreateInfo &info, Effect::Ptr_t effect,
      std::map<gapi::VertexSemantic, GeomVertexAttribBase::SharedPtr_t> attribs));

  MTHD_VIRTUAL(void bind());

  MTHD_VIRTUAL(void unbind());

  auto getBuffer(int idx) -> std::optional<gapi::BufferPtr_t> { return buffers_[idx]; }

  void updateUV(std::vector<UVData2> uvdata);

  void setUV(int index, std::array<math::vec2f_t, 4> coords);

protected:
  global::GapiPluginFunctionSet *gapiPlugin_;
  GeomBuilderPtr_t builder_;

private:
  gapi::VertexArrayPtr_t vao_;
  gapi::VertexAttribLayoutPtr_t attribLayout_;
  std::map<gapi::VertexSemantic, GeomVertexAttribBase::SharedPtr_t> attribs_;
  std::array<std::optional<gapi::BufferPtr_t>, Constants::MAX_IDX_BUFFERS> buffers_{};
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#include <sway/render/geom/geom.inl>

#endif  // SWAY_RENDER_GEOM_HPP
