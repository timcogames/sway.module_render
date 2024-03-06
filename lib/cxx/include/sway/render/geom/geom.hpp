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

class GeomBuilder;
class Geom {
public:
  Geom(global::GapiPluginFunctionSet *plug, GeomBuilder *builder);

  virtual ~Geom();

  template <class TObject>
  void call(std::function<void(TObject)> callback) {
    for (auto buf : buffers_) {
      if (buf.has_value()) {
        callback(buf.value());
      }
    }
  }

  MTHD_VIRTUAL(void create(const GeometryCreateInfo &info, EffectRef_t effect,
      std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs));

  MTHD_VIRTUAL(void bind()) {
    attribLayout_->enable();
    this->call<gapi::BufferPtr_t>(gapi::Buffer::BindFunctor());
  }

  MTHD_VIRTUAL(void unbind()) {
    this->call<gapi::BufferPtr_t>(gapi::Buffer::UnbindFunctor());
    attribLayout_->disable();
  }

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