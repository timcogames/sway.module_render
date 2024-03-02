#include <sway/render/geom/geombuilder.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

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

void GeomBuilder::create(int idx) {
  SAFE_DELETE_OBJECT(geometries_[idx]);
  geometries_[idx] = new Geom(gapiPlugin_, this);
}

auto GeomBuilder::canResize(std::size_t size) const -> bool { return size > geometries_.size(); }

void GeomBuilder::reserve(std::size_t size) {
  auto prevSize = geometries_.size();
  auto nextSize = math::util::clamp(size, Constants::MAX_BUFFER_OBJECTS, prevSize);
  if (!canResize(nextSize)) {
    return;
  }

  geometries_.resize(nextSize, nullptr);
  for (auto i = prevSize; i < geometries_.size(); i++) {
    this->create(i);
  }
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
