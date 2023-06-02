#ifndef SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_DEBUG_HPP
#define SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_DEBUG_HPP

#include <sway/math.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/geometryindexedvertexdata.hpp>
#include <sway/render/geometryvertexattribset.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/shape.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(procedurals)
NAMESPACE_BEGIN(prims)

template <typename TVertexDataType>
class Plane_Debug : public Shape {
public:
  void addLine(GeometryVertexAttribSet attribs, const math::vec3f_t &from, const math::vec3f_t &to) {
    attribs.pos->addVtxData(from);
    attribs.col->addVtxData(math::vec3f_t(1.0F, 0.0F, 0.0F));

    attribs.pos->addVtxData(to);
    attribs.col->addVtxData(math::vec3f_t(1.0F, 0.0F, 0.0F));
  }

  Plane_Debug(const math::size2f_t &size, const math::size2i_t &subdivisions)
      : data_(std::make_shared<GeometryIndexedVertexData<TVertexDataType>>(
            subdivisions.getW() * subdivisions.getH() + 4)) {
    auto sizeHalf = size / 2.0F;

    GeometryVertexAttribSet attribs = {
        .pos = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
        .col = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::COL),
        nullptr};

    auto unitScale = 0.8F;
    auto tileWt = size.getW() * unitScale;
    auto tileHt = size.getH() * unitScale;

    auto gridWt = subdivisions.getW() * tileWt;
    auto gridHt = subdivisions.getH() * tileHt;
    auto gridSizeHalf = math::size2f_t(gridWt / 2, gridHt / 2);

    for (auto col = 0; col < subdivisions.getW() + 1; ++col) {
      auto from = math::vec3f_t(-gridSizeHalf.getW(), tileHt * col - gridSizeHalf.getH(), 0.0F);
      auto to = math::vec3f_t(gridSizeHalf.getW(), tileHt * col - gridSizeHalf.getH(), 0.0F);

      addLine(attribs, from, to);
    }

    for (auto row = 0; row < subdivisions.getH() + 1; ++row) {
      auto from = math::vec3f_t(tileWt * row - gridSizeHalf.getW(), -gridSizeHalf.getH(), 0.0F);
      auto to = math::vec3f_t(tileWt * row - gridSizeHalf.getW(), gridSizeHalf.getH(), 0.0F);

      addLine(attribs, from, to);
    }
  }

  ~Plane_Debug() = default;

  [[nodiscard]] auto getGeometryData() const -> GeometryDataPtr<TVertexDataType> { return data_; }

  template <std::size_t TSize>
  void useVertexSemanticSet(std::array<sway::gapi::VertexSemantic, TSize> &arr) {
    data_->useVertexSemanticSet(arr);
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttribs() const -> VertexAttribMap_t) {  // clang-format on
    return data_->getAttribs();
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttrib(gapi::VertexSemantic semantic) const -> VertexAttribPtr_t) {  // clang-format on
    return data_->getAttrib(semantic);
  }

  // clang-format off
  MTHD_OVERRIDE(auto getGeometryInfo() const -> GeometryCreateInfo) {  // clang-format on
    GeometryCreateInfo info;

    info.topology = gapi::TopologyType::LINE_LIST;
    info.vb.desc.usage = gapi::BufferUsage::STATIC;
    info.vb.desc.byteStride = sizeof(TVertexDataType);
    info.vb.desc.capacity = data_->getVtxCount();
    info.vb.data = data_->getVtxRawdata();

    return info;
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertices() -> void *) {  // clang-format on
    return data_->getVtxRawdata();
  }

private:
  GeometryDataPtr<TVertexDataType> data_;
};

NAMESPACE_END(prims)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_DEBUG_HPP
