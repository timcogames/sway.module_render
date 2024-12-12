#ifndef SWAY_RENDER_GEOMBUILDER_HPP
#define SWAY_RENDER_GEOMBUILDER_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/effect/effect.hpp>
#include <sway/render/geom/_typedefs.hpp>
#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geomcreateinfo.hpp>
#include <sway/render/geom/geominstance.hpp>
#include <sway/render/global.hpp>
#include <sway/render/prereqs.hpp>

#include <list>
#include <map>
#include <memory>
#include <optional>
#include <vector>

NS_BEGIN_SWAY()
NS_BEGIN(render)

struct GeomPoolStats {
  u32_t numGeoms;

  GeomPoolStats()
      : numGeoms(0) {}
};

// BufferPool
class GeomBuilder {
public:
#pragma region "Static methods"

  static auto create(global::GapiPluginFunctionSet *plug, gapi::IdGeneratorPtr_t gen)
      -> GeomBuilderTypedefs::SharedPtr_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  GeomBuilder(global::GapiPluginFunctionSet *plug, gapi::IdGeneratorPtr_t gen);

  DTOR(GeomBuilder);

#pragma endregion

  template <typename TShape>
  auto create(int idx, const GeomCreateInfo &info, GeomVertexAttribSharedPtrMap_t attribs, EffectTypedefs::Ptr_t effect)
      -> u32_t;

  template <typename TShape>
  auto create(const GeomCreateInfo &info, GeomVertexAttribSharedPtrMap_t attribs, EffectTypedefs::Ptr_t effect)
      -> u32_t;

  template <typename TShape>
  auto createInstance(int idx, GeomInstanceDataDivisor<TShape> *divisor, const GeomCreateInfo &info,
      EffectTypedefs::Ptr_t effect) -> u32_t;

  template <typename TShape>
  auto createInstance(
      GeomInstanceDataDivisor<TShape> *divisor, const GeomCreateInfo &info, EffectTypedefs::Ptr_t effect) -> u32_t;

  void remove(u32_t idx);

  auto find(const std::string &uid) -> GeomTypedefs::Ptr_t;

  auto canResize(std::size_t size) const -> bool;

  void reserve(std::size_t size);

  auto getGeometries() -> GeomTypedefs::Container_t { return geometries_; }

  auto getGeometry(u32_t idx) -> GeomTypedefs::Ptr_t;

  auto getIdGenerator() -> gapi::IdGeneratorPtr_t { return idGenerator_; }

  GeomPoolStats stats_;

private:
  global::GapiPluginFunctionSet *gapiPlugin_;
  gapi::IdGeneratorPtr_t idGenerator_;
  GeomTypedefs::Container_t geometries_;
  std::list<u32_t> availables_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#include <sway/render/geom/geombuilder.inl>

#endif  // SWAY_RENDER_GEOMBUILDER_HPP
