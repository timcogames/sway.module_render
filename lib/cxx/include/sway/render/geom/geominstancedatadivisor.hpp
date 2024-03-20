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
  GeomInstanceDataDivisor(std::size_t numInsts)
      : offsetIndex_(0) {
    instances_.reserve(std::min(numInsts, Constants::MAX_NUM_INSTANCES));
  }

  ~GeomInstanceDataDivisor() { instances_.clear(); }

  void addInstanceData() {
    if (instances_.size() > Constants::MAX_NUM_INSTANCES) {
      return;
    }

    auto *shape = new TShape({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
    for (auto i = 0; i < shape->data()->getElmSize(); ++i) {
      auto oldIndex = shape->data()->at(i);
      auto newIndex = oldIndex + offsetIndex_;

      shape->data()->setData(i, newIndex);
    }

    instances_.push_back(shape);

    // clang-format off
    offsetIndex_ = static_cast<u32_t>(*std::max_element(
      instances_.back()->data()->getElements(), instances_.back()->data()->getElements() + shape->data()->getElmSize())) + 1;
    // clang-format on
  }

  auto getInstSize() const -> std::size_t { return instances_.size(); }

  auto at(u32_t idx) -> TShape * { return idx > instances_.size() ? nullptr : instances_[idx]; }

  auto getIndices() -> std::array<u32_t, TShape::MAX_QUAD_RESERVE_ELEMENTS * 3> {
    std::array<u32_t, TShape::MAX_QUAD_RESERVE_ELEMENTS * 3> indices;
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
  std::vector<TShape *> instances_;
  u32_t offsetIndex_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMINSTANCEDATADIVISOR_HPP
