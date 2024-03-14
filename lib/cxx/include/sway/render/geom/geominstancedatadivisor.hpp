#ifndef SWAY_RENDER_GEOMINSTANCEDATADIVISOR_HPP
#define SWAY_RENDER_GEOMINSTANCEDATADIVISOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/geom/geomindexedvertexdata.hpp>

#include <algorithm>  // std::max_element
#include <memory>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TVertexDataType>
class GeomInstanceDataDivisor {
public:
  GeomInstanceDataDivisor(std::size_t numInsts) {
    instances_.reserve(std::min(numInsts, Constants::MAX_NUM_INSTANCES));
  }

  ~GeomInstanceDataDivisor() { instances_.clear(); }

  void addInstanceData(std::shared_ptr<GeomIndexedVertexData<TVertexDataType, u32_t>> data) {
    if (instances_.size() > Constants::MAX_NUM_INSTANCES) {
      return;
    }

    for (auto i = 0; i < data->getElmSize(); ++i) {
      auto oldIndex = data->at(i);
      auto newIndex = oldIndex + offsetIndex_;

      data->setData(i, newIndex);
    }

    instances_.push_back(data);

    // clang-format off
    offsetIndex_ = static_cast<u32_t>(*std::max_element(
      instances_.back()->getElements(), instances_.back()->getElements() + data->getElmSize())) + 1;
    // clang-format on
  }

  auto getInstSize() const -> std::size_t { return instances_.size(); }

private:
  std::vector<std::shared_ptr<GeomIndexedVertexData<TVertexDataType, u32_t>>> instances_;
  u32_t offsetIndex_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMINSTANCEDATADIVISOR_HPP
