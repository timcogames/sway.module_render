#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect.hpp>
#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geominstance.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/global.hpp>

#include <algorithm>  // std::find
#include <map>
#include <memory>
#include <optional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TShape>
auto GeomBuilder::create(const GeometryCreateInfo &info,
    std::map<gapi::VertexSemantic, GeomVertexAttribBase::SharedPtr_t> attribs, Effect::Ptr_t effect) -> u32_t {
  return create<TShape>(availables_.front(), info, attribs, effect);
}

template <typename TShape>
auto GeomBuilder::create(int idx, const GeometryCreateInfo &info,
    std::map<gapi::VertexSemantic, GeomVertexAttribBase::SharedPtr_t> attribs, Effect::Ptr_t effect) -> u32_t {
  SAFE_DELETE_OBJECT(geometries_[idx]);
  geometries_[idx] = new Geom(gapiPlugin_, this);
  geometries_[idx]->create(info, effect, attribs);

  availables_.remove_if([&](int i) { return i == idx; });

  return idx;
}

template <typename TShape>
auto GeomBuilder::createInstance(
    GeomInstanceDataDivisor<TShape> *divisor, const GeometryCreateInfo &info, Effect::Ptr_t effect) -> u32_t {
  return createInstance<TShape>(availables_.front(), divisor, info, effect);
}

template <typename TShape>
auto GeomBuilder::createInstance(
    int idx, GeomInstanceDataDivisor<TShape> *divisor, const GeometryCreateInfo &info, Effect::Ptr_t effect) -> u32_t {
  SAFE_DELETE_OBJECT(geometries_[idx]);
  geometries_[idx] = new GeomInstance<TShape>(gapiPlugin_, this, divisor);
  geometries_[idx]->create(info, effect, divisor->getVertexAttribs());

  availables_.remove_if([&](int i) { return i == idx; });

  return idx;
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
