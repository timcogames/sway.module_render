#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect.hpp>
#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geominstance.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/global.hpp>

#include <map>
#include <memory>
#include <optional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TShape>
auto GeomBuilder::create(int idx, const GeometryCreateInfo &info,
    std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs,
    EffectPtr_t effect) -> std::optional<std::string> {
  SAFE_DELETE_OBJECT(geometries_[idx]);
  geometries_[idx] = new Geom(gapiPlugin_, this);
  geometries_[idx]->create(info, effect, attribs);

  return geometries_[idx]->getUid();
}

template <typename TShape>
auto GeomBuilder::createInstance(int idx, GeomInstanceDataDivisor<TShape> *divisor, const GeometryCreateInfo &info,
    EffectPtr_t effect) -> std::optional<std::string> {
  SAFE_DELETE_OBJECT(geometries_[idx]);
  geometries_[idx] = new GeomInstance<TShape>(gapiPlugin_, this, divisor);
  geometries_[idx]->create(info, effect, divisor->getVertexAttribs());

  return geometries_[idx]->getUid();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
