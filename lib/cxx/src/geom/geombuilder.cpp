#include <sway/render/geom/geombuilder.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

auto GeomBuilder::create(gapi::IdGeneratorPtr_t gen) -> std::shared_ptr<GeomBuilder> {
  return std::make_shared<GeomBuilder>(global::getGapiPluginFunctionSet(), gen);
}

GeomBuilder::GeomBuilder(global::GapiPluginFunctionSet *plug, gapi::IdGeneratorPtr_t gen)
    : gapiPlugin_(plug)
    , idGenerator_(gen) {}

GeomBuilder::~GeomBuilder() {
  auto iter = geometries_.begin();
  while (iter != geometries_.end()) {
    SAFE_DELETE_OBJECT(*iter);
    iter = geometries_.erase(iter);
  }
}

auto GeomBuilder::create(int idx, const GeometryCreateInfo &info,
    std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs,
    EffectPtr_t effect) -> std::optional<std::string> {
  SAFE_DELETE_OBJECT(geometries_[idx]);
  geometries_[idx] = new Geom(gapiPlugin_, this);
  geometries_[idx]->create(info, effect, attribs);

  return geometries_[idx]->getUid();
}

auto GeomBuilder::canResize(std::size_t size) const -> bool { return size > geometries_.size(); }

void GeomBuilder::reserve(std::size_t size) {
  auto prevSize = geometries_.size();
  auto nextSize = math::util::clamp(size, Constants::MAX_BUFFER_OBJECTS, prevSize);
  if (!canResize(nextSize)) {
    return;
  }

  geometries_.resize(nextSize, nullptr);
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
