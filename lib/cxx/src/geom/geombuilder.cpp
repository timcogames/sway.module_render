#include <sway/render/geom/geombuilder.hpp>

namespace sway::render {

auto GeomBuilder::create(global::GapiPluginFunctionSet *plug, gapi::typedefs::IdGeneratorPtr_t gen)
    -> GeomBuilderTypedefs::SharedPtr_t {
  return std::make_shared<GeomBuilder>(plug, gen);
}

GeomBuilder::GeomBuilder(global::GapiPluginFunctionSet *plug, gapi::typedefs::IdGeneratorPtr_t gen)
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

auto GeomBuilder::find(const std::string &uid) -> GeomTypedefs::Ptr_t {
  auto iter = std::find_if(geometries_.begin(), geometries_.end(),
      [&uid](const auto &geom) { return geom && geom->getUniqueId().value() == uid; });
  if (iter != geometries_.end()) {
    return *iter;
  }

  return nullptr;
}

auto GeomBuilder::canResize(std::size_t size) const -> bool { return size > geometries_.size(); }

void GeomBuilder::reserve(std::size_t size) {
  auto prevSize = geometries_.size();
  auto nextSize = math::clamp(size, Constants::MAX_BUFFER_OBJECTS, prevSize);
  if (!canResize(nextSize)) {
    return;
  }

  geometries_.resize(nextSize, nullptr);
  for (auto i = 0; i < geometries_.size(); i++) {
    availables_.push_back(i);
  }
}

auto GeomBuilder::getGeometry(u32_t idx) -> GeomTypedefs::Ptr_t {
  if (idx >= geometries_.size()) {
    return nullptr;
  }

  return geometries_[idx];
}

}  // namespace sway::render
