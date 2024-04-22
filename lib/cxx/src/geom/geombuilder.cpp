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

void GeomBuilder::remove(u32_t idx) {
  auto iter = geometries_.begin() + idx;
  SAFE_DELETE_OBJECT(*iter);
  geometries_.erase(iter);

  availables_.push_back(idx);
}

auto GeomBuilder::find(const std::string &uid) -> Geom::Ptr {
  for (auto item : geometries_) {
    if (item->getUid().value() == uid) {
      return item;
    }
  }

  return nullptr;
}

auto GeomBuilder::canResize(std::size_t size) const -> bool { return size > geometries_.size(); }

void GeomBuilder::reserve(std::size_t size) {
  auto prevSize = geometries_.size();
  auto nextSize = math::util::clamp(size, Constants::MAX_BUFFER_OBJECTS, prevSize);
  if (!canResize(nextSize)) {
    return;
  }

  geometries_.resize(nextSize, nullptr);
  for (auto i = 0; i < geometries_.size(); i++) {
    availables_.push_back(i);
  }
}

auto GeomBuilder::getGeometry(int idx) -> Geom::Ptr {
  if (idx >= geometries_.size() - 1) {
    return nullptr;
  }

  return geometries_[idx];
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
