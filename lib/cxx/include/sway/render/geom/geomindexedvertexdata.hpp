#ifndef SWAY_RENDER_GEOMINDEXEDVERTEXDATA_HPP
#define SWAY_RENDER_GEOMINDEXEDVERTEXDATA_HPP

#include <sway/core.hpp>
#include <sway/render/geom/geomvertexdata.hpp>
#include <sway/render/prereqs.hpp>

#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TVertexDataType, typename TElementDataType>
class GeomIndexedVertexData : public GeomVertexData<TVertexDataType> {
public:
  GeomIndexedVertexData(u32_t numVerts, u32_t numElems)
      : GeomVertexData<TVertexDataType>(numVerts)
      , numElems_(numElems) {
    elements_ = new TElementDataType[numElems_ * sizeof(TElementDataType)];
  }

  virtual ~GeomIndexedVertexData() { SAFE_DELETE_ARRAY(elements_); }

  void setData(u32_t idx, u32_t elm) { elements_[idx] = elm; }

  void setTriElements(u32_t offset, u32_t a, u32_t b, u32_t c) {
    setData(0 + offset, a);
    setData(1 + offset, b);
    setData(2 + offset, c);
  }

  auto getElements() -> TElementDataType * { return elements_; }

  [[nodiscard]]
  auto getElmSize() const -> u32_t {
    return numElems_;
  }

private:
  TElementDataType *elements_;
  u32_t numElems_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMINDEXEDVERTEXDATA_HPP
