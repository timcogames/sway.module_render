#ifndef SWAY_RENDER_GEOMBUILDER_HPP
#define SWAY_RENDER_GEOMBUILDER_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect.hpp>
#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geominstance.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/global.hpp>

#include <algorithm>
#include <array>
#include <optional>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class GeomBuilder {
public:
  static auto create(gapi::IdGeneratorPtr_t gen) -> std::shared_ptr<GeomBuilder>;

  GeomBuilder(global::GapiPluginFunctionSet *plug, gapi::IdGeneratorPtr_t gen);

  ~GeomBuilder();

  void create(int idx);

  template <typename TShape>
  auto createInstance(int idx, GeomInstanceDataDivisor<TShape> *divisor, const GeometryCreateInfo &info,
      EffectPtr_t effect) -> std::optional<std::string> {
    SAFE_DELETE_OBJECT(geometries_[idx]);
    geometries_[idx] = new GeomInstance<TShape>(gapiPlugin_, this, divisor);
    geometries_[idx]->create(info, effect, divisor->getVertexAttribs());

    return geometries_[idx]->getUid();
  }

  void remove(u32_t idx) {
    auto iter = geometries_.begin() + idx;
    SAFE_DELETE_OBJECT(*iter);
    geometries_.erase(iter);
  }

  auto find(const std::string &uid) -> Geom * {
    for (auto item : geometries_) {
      if (item->getUid().value() == uid) {
        return item;
      }
    }

    return nullptr;
  }

  auto canResize(std::size_t size) const -> bool;

  void reserve(std::size_t size);

  auto getGeometries() -> std::vector<Geom *> { return geometries_; }

  auto getGeometry(int idx) -> Geom * { return geometries_[idx]; }

  auto getIdGenerator() -> gapi::IdGeneratorPtr_t { return idGenerator_; }

private:
  global::GapiPluginFunctionSet *gapiPlugin_;
  gapi::IdGeneratorPtr_t idGenerator_;
  std::vector<Geom *> geometries_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMBUILDER_HPP
