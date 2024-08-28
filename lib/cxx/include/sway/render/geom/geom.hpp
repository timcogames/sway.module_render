#ifndef SWAY_RENDER_GEOM_HPP
#define SWAY_RENDER_GEOM_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect.hpp>
#include <sway/render/geom/geomvertexattribbase.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/global.hpp>

#include <algorithm>
#include <array>
#include <optional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

#define QUAD_TEXCOORD_SIZE2 4

struct UVData2 {
  std::vector<math::vec2f_t> uv;
};

class GeomBuilder;

class Geom : public core::foundation::Uniqueable<std::string> {
public:
  using Ptr = Geom *;

  Geom(global::GapiPluginFunctionSet *plug, GeomBuilder *builder);

  virtual ~Geom();

  template <class TObject>
  void call(std::function<void(TObject)> callback);

  MTHD_VIRTUAL(void create(const GeometryCreateInfo &info, EffectPtr_t effect,
      std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs));

  MTHD_VIRTUAL(void bind());

  MTHD_VIRTUAL(void unbind());

  auto getBuffer(int idx) -> std::optional<gapi::BufferPtr_t> { return buffers_[idx]; }

  void updateUV(std::vector<UVData2> uvdata);

  void setUV(int index, std::array<math::vec2f_t, 4> coords);

protected:
  global::GapiPluginFunctionSet *gapiPlugin_;
  GeomBuilder *builder_;

private:
  gapi::VertexAttribLayoutPtr_t attribLayout_;
  std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs_;
  std::array<std::optional<gapi::BufferPtr_t>, Constants::MAX_IDX_BUFFERS> buffers_{};
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#include <sway/render/geom/geom.inl>

#endif  // SWAY_RENDER_GEOM_HPP
