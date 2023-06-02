#ifndef SWAY_RENDER_PROCEDURALS_GUIDES_AXIS_HPP
#define SWAY_RENDER_PROCEDURALS_GUIDES_AXIS_HPP

#include <sway/math.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/geometryindexedvertexdata.hpp>
#include <sway/render/geometryvertexattribset.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/shape.hpp>

#include <memory>

#define AXIS_VERTEX_COUNT 9  // Количество вершин.
#define COLOR_R math::vec3f_t(1.0F, 0.0F, 0.0F)
#define COLOR_G math::vec3f_t(0.0F, 1.0F, 0.0F)
#define COLOR_B math::vec3f_t(0.0F, 0.0F, 1.0F)

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(procedurals)
NAMESPACE_BEGIN(guides)

template <typename TVertexDataType>
using GeometryDataPtr = std::shared_ptr<GeometryIndexedVertexData<TVertexDataType>>;

template <typename TVertexDataType>
class Axis : public Shape {
public:
  Axis(const math::size2f_t &size)
      : data_(std::make_shared<GeometryIndexedVertexData<TVertexDataType>>(AXIS_VERTEX_COUNT)) {
    GeometryVertexAttribSet attribs = {
        .pos = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
        .col = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::COL),
        nullptr};

    // X axis
    attribs.pos->addVtxData({+0.0F, +0.0F, +0.0F});
    attribs.pos->addVtxData({+1.0F, +0.0F, +0.0F});
    attribs.pos->addVtxData({+0.9F, +0.1F, +0.0F});
    attribs.pos->addVtxData({+0.9F, -0.1F, +0.0F});
    // Y axis
    attribs.pos->addVtxData({+0.0F, +0.0F, +0.0F});
    attribs.pos->addVtxData({+0.0F, +1.0F, +0.0F});
    attribs.pos->addVtxData({+0.1F, +0.9F, +0.0F});
    attribs.pos->addVtxData({-0.1F, +0.9F, +0.0F});
    // Z axis
    attribs.pos->addVtxData({+0.0F, +0.0F, +0.0F});
    attribs.pos->addVtxData({+0.0F, +0.0F, +1.0F});
    attribs.pos->addVtxData({+0.1F, +0.0F, +0.9F});
    attribs.pos->addVtxData({-0.1F, +0.0F, +0.9F});

    // X axis
    attribs.col->addVtxData(COLOR_R);
    attribs.col->addVtxData(COLOR_R);
    attribs.col->addVtxData(COLOR_R);
    attribs.col->addVtxData(COLOR_R);
    // Y axis
    attribs.col->addVtxData(COLOR_G);
    attribs.col->addVtxData(COLOR_G);
    attribs.col->addVtxData(COLOR_G);
    attribs.col->addVtxData(COLOR_G);
    // Z axis
    attribs.col->addVtxData(COLOR_B);
    attribs.col->addVtxData(COLOR_B);
    attribs.col->addVtxData(COLOR_B);
    attribs.col->addVtxData(COLOR_B);

    // X axis
    data_->addIdxData(0);
    data_->addIdxData(1);
    data_->addIdxData(1);
    data_->addIdxData(2);
    data_->addIdxData(1);
    data_->addIdxData(3);
    // Y axis
    data_->addIdxData(4);
    data_->addIdxData(5);
    data_->addIdxData(5);
    data_->addIdxData(6);
    data_->addIdxData(5);
    data_->addIdxData(7);
    // Z axis
    data_->addIdxData(8);
    data_->addIdxData(9);
    data_->addIdxData(9);
    data_->addIdxData(10);
    data_->addIdxData(9);
    data_->addIdxData(11);
  }

  ~Axis() = default;

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

    info.ib.desc.usage = gapi::BufferUsage::STATIC;
    info.ib.desc.byteStride = sizeof(u32_t);
    info.ib.desc.capacity = data_->getIdxCount();
    info.ib.data = data_->getIndices().data();

    return info;
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertices() -> void *) {  // clang-format on
    return data_->getVtxRawdata();
  }

private:
  GeometryDataPtr<TVertexDataType> data_;
};

NAMESPACE_END(guides)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_GUIDES_AXIS_HPP
