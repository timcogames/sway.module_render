#ifndef SWAY_RENDER_GEOMINSTANCEDATADIVISOR_HPP
#define SWAY_RENDER_GEOMINSTANCEDATADIVISOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/geom/geomindexedvertexdata.hpp>
#include <sway/render/procedurals/prims/quadrilateral.hpp>

#include <algorithm>  // std::max_element
#include <memory>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TShape>
class GeomInstanceDataDivisor {
public:
  GeomInstanceDataDivisor(const std::initializer_list<gapi::VertexSemantic> &semantics, std::size_t numInsts)
      : semantics_(semantics)
      , offsetIndex_(0) {
    instances_.reserve(std::min(numInsts, Constants::MAX_NUM_INSTANCES));
  }

  ~GeomInstanceDataDivisor() { instances_.clear(); }

  template <typename TResult = GeomIndexedVertexData<typename TShape::VtxDataType_t, typename TShape::IdxDataType_t>>
  auto toIndexedVertexData(TShape *shape) -> std::shared_ptr<TResult> {
    return std::static_pointer_cast<TResult>(shape->data());
  }

  void addInstanceData() {
    if (instances_.size() > Constants::MAX_NUM_INSTANCES) {
      return;
    }

    auto *shape = new TShape({});
    shape->data()->useSemanticSet(semantics_.begin(), semantics_.end());
    if (shape->isIndexed()) {
      for (auto i = 0; i < toIndexedVertexData(shape)->getElmSize(); ++i) {
        auto oldIndex = toIndexedVertexData(shape)->at(i);
        auto newIndex = oldIndex + offsetIndex_;

        toIndexedVertexData(shape)->setData(i, newIndex);
      }
    }

    instances_.push_back(shape);

    if (shape->isIndexed()) {
      // clang-format off
      offsetIndex_ = static_cast<u32_t>(*std::max_element(
        toIndexedVertexData(instances_.back())->getElements(), 
        toIndexedVertexData(instances_.back())->getElements() + toIndexedVertexData(shape)->getElmSize())) + 1;
      // clang-format on
    }
  }

  auto getInstSize() const -> std::size_t { return instances_.size(); }

  auto at(u32_t idx) -> TShape * { return idx > instances_.size() ? nullptr : instances_[idx]; }

  template <std::size_t TInstSize>
  auto getIndices() -> std::array<u32_t, TShape::MAX_QUAD_RESERVE_ELEMENTS * TInstSize> {
    std::array<u32_t, TShape::MAX_QUAD_RESERVE_ELEMENTS * TInstSize> indices;
    u32_t idx = 0;
    for (auto i = 0; i < instances_.size(); ++i) {
      for (auto elm = 0; elm < instances_[i]->data()->getElmSize(); ++elm) {
        indices[idx] = instances_[i]->data()->getElements()[elm];
        idx += 1;
      }
    }

    return indices;
  }

  auto getVertexAttribs() const -> std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> {
    return instances_[0]->data()->getAttribs();
  }

private:
  std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs_;
  std::vector<gapi::VertexSemantic> semantics_;
  std::vector<TShape *> instances_;
  u32_t offsetIndex_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMINSTANCEDATADIVISOR_HPP
