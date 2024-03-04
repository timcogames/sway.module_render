#include <sway/render/geom/geombuilder.hpp>
#include <sway/render/geom/geominstance.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

GeomInstance::GeomInstance(global::GapiPluginFunctionSet *plug, GeomBuilder *builder)
    : Geom(plug, builder) {}

void GeomInstance::create(const GeometryCreateInfo &info) {
  vao_ = gapiPlugin_->createVertexArray();
  Geom::create(info);
}

void GeomInstance::bind() {
  vao_->bind();
  Geom::bind();
}

void GeomInstance::unbind() {
  Geom::unbind();
  vao_->unbind();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
