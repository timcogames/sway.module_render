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

  template <typename TVertexDataType>
  void createInstance(int idx, GeomInstanceDataDivisor<TVertexDataType> *divisor, const GeometryCreateInfo &info,
      EffectPtr_t effect, std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs) {
    SAFE_DELETE_OBJECT(geometries_[idx]);
    geometries_[idx] = new GeomInstance(gapiPlugin_, this);
    static_cast<GeomInstance *>(geometries_[idx])->create<TVertexDataType>(divisor, info, effect, attribs);
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
