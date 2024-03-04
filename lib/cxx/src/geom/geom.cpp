#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geombuilder.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Geom::Geom(global::GapiPluginFunctionSet *plug, GeomBuilder *builder)
    : gapiPlugin_(plug)
    , builder_(builder) {}

Geom::~Geom() { std::fill(buffers_.begin(), buffers_.end(), std::nullopt); }

void Geom::create(const GeometryCreateInfo &info) {
  auto createBuffers = [&, next = 0](std::optional<gapi::BufferPtr_t> &buf) mutable {
    if (next == Constants::IDX_EBO && !info.indexed) {
      return;
    }

    buf = std::make_optional<gapi::BufferPtr_t>(gapiPlugin_->createBuffer(builder_->getIdGenerator(), info.bo[next]));
    ++next;
  };

  std::for_each(buffers_.begin(), buffers_.end(), createBuffers);
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
