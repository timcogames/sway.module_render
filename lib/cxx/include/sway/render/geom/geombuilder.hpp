#ifndef SWAY_RENDER_GEOMBUILDER_HPP
#define SWAY_RENDER_GEOMBUILDER_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect.hpp>
#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geominstance.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/global.hpp>
#include <sway/render/prereqs.hpp>

#include <list>
#include <map>
#include <memory>
#include <optional>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct GeomPoolStats {
  u32_t numGeoms;

  GeomPoolStats()
      : numGeoms(0) {}
};

// BufferPool
class GeomBuilder {
  DECLARE_CLASS_POINTER_ALIASES(GeomBuilder)

public:
#pragma region "Static methods"

  static auto create(gapi::IdGeneratorPtr_t gen) -> GeomBuilder::SharedPtr_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  GeomBuilder(global::GapiPluginFunctionSet *plug, gapi::IdGeneratorPtr_t gen);

  ~GeomBuilder();

#pragma endregion

  template <typename TShape>
  auto create(int idx, const GeometryCreateInfo &info,
      std::map<gapi::VertexSemantic, GeomVertexAttribBase::SharedPtr_t> attribs, Effect::Ptr_t effect) -> u32_t;

  template <typename TShape>
  auto create(const GeometryCreateInfo &info, std::map<gapi::VertexSemantic, GeomVertexAttribBase::SharedPtr_t> attribs,
      Effect::Ptr_t effect) -> u32_t;

  template <typename TShape>
  auto createInstance(
      int idx, GeomInstanceDataDivisor<TShape> *divisor, const GeometryCreateInfo &info, Effect::Ptr_t effect) -> u32_t;

  template <typename TShape>
  auto createInstance(
      GeomInstanceDataDivisor<TShape> *divisor, const GeometryCreateInfo &info, Effect::Ptr_t effect) -> u32_t;

  void remove(u32_t idx);

  auto find(const std::string &uid) -> Geom::Ptr_t;

  auto canResize(std::size_t size) const -> bool;

  void reserve(std::size_t size);

  auto getGeometries() -> std::vector<Geom::Ptr_t> { return geometries_; }

  auto getGeometry(int idx) -> Geom::Ptr_t;

  auto getIdGenerator() -> gapi::IdGeneratorPtr_t { return idGenerator_; }

  GeomPoolStats stats_;

private:
  global::GapiPluginFunctionSet *gapiPlugin_;
  gapi::IdGeneratorPtr_t idGenerator_;
  std::vector<Geom::Ptr_t> geometries_;
  std::list<u32_t> availables_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#include <sway/render/geom/geombuilder.inl>

#endif  // SWAY_RENDER_GEOMBUILDER_HPP
