#ifndef SWAY_RENDER_GEOM_HPP
#define SWAY_RENDER_GEOM_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/global.hpp>

#include <algorithm>
#include <array>
#include <optional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class GeomBuilder;
class Geom {
public:
  Geom(global::GapiPluginFunctionSet *plug, GeomBuilder *builder);

  virtual ~Geom();

  MTHD_VIRTUAL(void create(const GeometryCreateInfo &info));

  auto getBuffer(int idx) -> std::optional<gapi::BufferPtr_t> { return buffers_[idx]; }

protected:
  global::GapiPluginFunctionSet *gapiPlugin_;
  GeomBuilder *builder_;

private:
  gapi::VertexAttribLayoutPtr_t attribLayout_;
  std::array<std::optional<gapi::BufferPtr_t>, Constants::MAX_IDX_BUFFERS> buffers_{};
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOM_HPP
