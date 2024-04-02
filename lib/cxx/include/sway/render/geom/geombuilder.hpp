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
#include <map>
#include <memory>
#include <optional>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct GeomPoolStats {
  u32_t totalNumGeometries;

  GeomPoolStats()
      : totalNumGeometries(0) {}
};

// BufferPool
class GeomBuilder {
public:
  static auto create(gapi::IdGeneratorPtr_t gen) -> std::shared_ptr<GeomBuilder>;

  GeomBuilder(global::GapiPluginFunctionSet *plug, gapi::IdGeneratorPtr_t gen);

  ~GeomBuilder();

  template <typename TShape>
  auto create(int idx, const GeometryCreateInfo &info,
      std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs,
      EffectPtr_t effect) -> std::optional<std::string>;

  template <typename TShape>
  auto createInstance(int idx, GeomInstanceDataDivisor<TShape> *divisor, const GeometryCreateInfo &info,
      EffectPtr_t effect) -> std::optional<std::string>;

  void remove(u32_t idx);

  auto find(const std::string &uid) -> Geom *;

  auto canResize(std::size_t size) const -> bool;

  void reserve(std::size_t size);

  auto getGeometries() -> std::vector<Geom *> { return geometries_; }

  auto getGeometry(int idx) -> Geom * { return geometries_[idx]; }

  auto getIdGenerator() -> gapi::IdGeneratorPtr_t { return idGenerator_; }

  GeomPoolStats stats_;

private:
  global::GapiPluginFunctionSet *gapiPlugin_;
  gapi::IdGeneratorPtr_t idGenerator_;
  std::vector<Geom *> geometries_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#include <sway/render/geom/geombuilder.inl>

#endif  // SWAY_RENDER_GEOMBUILDER_HPP
