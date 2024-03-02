#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geombuilder.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Geom::Geom(global::GapiPluginFunctionSet *plug, GeomBuilder *builder)
    : gapiPlugin_(plug)
    , builder_(builder) {}

Geom::~Geom() {
  buffers_[0] = std::nullopt;
  std::fill(buffers_.begin(), buffers_.end(), std::nullopt);
}

void Geom::create(const GeometryCreateInfo &info) {
  // attribLayout_ = gapiPlugin_->createVertexAttribLayout(effect_->getShaderProgram());
  // for (const auto &attrib : data->getAttribs()) {
  //   attribLayout_->addAttribute(attrib.second->getDescriptor());
  // }

  auto createBuffers = [&, bufIdx = 0](std::optional<gapi::BufferPtr_t> &buf) mutable {
    if (bufIdx == Constants::IDX_IBO && !info.indexed) {
      return;
    }

    buf = std::make_optional<gapi::BufferPtr_t>(gapiPlugin_->createBuffer(builder_->getIdGenerator(), info.bo[bufIdx]));
    ++bufIdx;
  };

  std::for_each(buffers_.begin(), buffers_.end(), createBuffers);
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
