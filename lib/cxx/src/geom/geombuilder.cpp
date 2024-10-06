#include <sway/render/geom/geombuilder.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

auto GeomBuilder::create(gapi::IdGeneratorPtr_t gen) -> GeomBuilder::SharedPtr_t {
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
  // geometries_.erase(iter);
  geometries_[idx] = nullptr;

  availables_.push_back(idx);
}

auto GeomBuilder::find(const std::string &uid) -> Geom::Ptr_t {
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

auto GeomBuilder::getGeometry(int idx) -> Geom::Ptr_t {
  if (idx >= geometries_.size()) {
    return nullptr;
  }

  return geometries_[idx];
}

NS_END()  // namespace render
NS_END()  // namespace sway
