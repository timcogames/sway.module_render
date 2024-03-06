#ifndef SWAY_RENDER_GEOMINSTANCE_HPP
#define SWAY_RENDER_GEOMINSTANCE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/geom/geom.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class GeomBuilder;
class GeomInstance : public Geom {
public:
  GeomInstance(global::GapiPluginFunctionSet *plug, GeomBuilder *builder);

  virtual ~GeomInstance() = default;

  MTHD_OVERRIDE(void create(const GeometryCreateInfo &info, EffectRef_t effect,
      std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs));

  MTHD_OVERRIDE(void bind());

  MTHD_OVERRIDE(void unbind());

private:
  gapi::VertexArrayPtr_t vao_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMINSTANCE_HPP