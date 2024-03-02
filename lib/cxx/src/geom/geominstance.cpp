#include <sway/render/geom/geombuilder.hpp>
#include <sway/render/geom/geominstance.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

GeomInstance::GeomInstance(global::GapiPluginFunctionSet *plug, GeomBuilder *builder)
    : Geom(plug, builder) {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
