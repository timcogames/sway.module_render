#ifndef SWAY_RENDER_GEOMETRYINDEXEDVERTEXDATA_HPP
#define SWAY_RENDER_GEOMETRYINDEXEDVERTEXDATA_HPP

#include <sway/core.hpp>
#include <sway/render/geometryvertexdata.hpp>
#include <sway/render/prereqs.hpp>

#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TVertexDataType>
class GeometryIndexedVertexData : public GeometryVertexData<TVertexDataType> {
public:
  GeometryIndexedVertexData(s32_t vtxcount)
      : GeometryVertexData<TVertexDataType>(vtxcount) {}

  ~GeometryIndexedVertexData() = default;

  void addIdxData(u32_t idx) { indices_.push_back(idx); }

  void addTriIndices(u32_t a, u32_t b, u32_t c) {
    addIdxData(a);
    addIdxData(b);
    addIdxData(c);
  }

  auto getIndices() -> std::vector<u32_t> & { return indices_; }

  [[nodiscard]] auto getIdxCount() const -> u32_t { return indices_.size(); }

private:
  std::vector<u32_t> indices_;
};

template <typename TVertexDataType>
using GeometryDataPtr = std::shared_ptr<GeometryIndexedVertexData<TVertexDataType>>;

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMETRYINDEXEDVERTEXDATA_HPP
