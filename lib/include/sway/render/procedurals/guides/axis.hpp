#ifndef SWAY_RENDER_PROCEDURALS_GUIDES_AXIS_HPP
#define SWAY_RENDER_PROCEDURALS_GUIDES_AXIS_HPP

#include <sway/math.hpp>
#include <sway/render/geometryindexedvertexdata.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/shape.hpp>

#include <memory>

#define AXIS_VERTEX_COUNT 9  // Количество вершин.
#define COLOR_R math::col4f_t(1.0F, 0.0F, 0.0F, 1.0F).toVec4()
#define COLOR_G math::col4f_t(0.0F, 1.0F, 0.0F, 1.0F).toVec4()
#define COLOR_B math::col4f_t(0.0F, 0.0F, 1.0F, 1.0F).toVec4()

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
    auto posAttribCapacity = 0;
    auto posAttrib = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::POS);
    // X axis
    posAttrib->addVtxData({+0.0F, +0.0F, +0.0F}, posAttribCapacity);
    posAttrib->addVtxData({+1.0F, +0.0F, +0.0F}, posAttribCapacity);
    posAttrib->addVtxData({+0.9F, +0.1F, +0.0F}, posAttribCapacity);
    posAttrib->addVtxData({+0.9F, -0.1F, +0.0F}, posAttribCapacity);
    // Y axis
    posAttrib->addVtxData({+0.0F, +0.0F, +0.0F}, posAttribCapacity);
    posAttrib->addVtxData({+0.0F, +1.0F, +0.0F}, posAttribCapacity);
    posAttrib->addVtxData({+0.1F, +0.9F, +0.0F}, posAttribCapacity);
    posAttrib->addVtxData({-0.1F, +0.9F, +0.0F}, posAttribCapacity);
    // Z axis
    posAttrib->addVtxData({+0.0F, +0.0F, +0.0F}, posAttribCapacity);
    posAttrib->addVtxData({+0.0F, +0.0F, +1.0F}, posAttribCapacity);
    posAttrib->addVtxData({+0.1F, +0.0F, +0.9F}, posAttribCapacity);
    posAttrib->addVtxData({-0.1F, +0.0F, +0.9F}, posAttribCapacity);

    auto colAttribCapacity = 0;
    auto colAttrib = data_->template createVertexAttrib<math::vec4f_t>(gapi::VertexSemantic::COL);
    // X axis
    colAttrib->addVtxData(COLOR_R, colAttribCapacity);
    colAttrib->addVtxData(COLOR_R, colAttribCapacity);
    colAttrib->addVtxData(COLOR_R, colAttribCapacity);
    colAttrib->addVtxData(COLOR_R, colAttribCapacity);
    // Y axis
    colAttrib->addVtxData(COLOR_G, colAttribCapacity);
    colAttrib->addVtxData(COLOR_G, colAttribCapacity);
    colAttrib->addVtxData(COLOR_G, colAttribCapacity);
    colAttrib->addVtxData(COLOR_G, colAttribCapacity);
    // Z axis
    colAttrib->addVtxData(COLOR_B, colAttribCapacity);
    colAttrib->addVtxData(COLOR_B, colAttribCapacity);
    colAttrib->addVtxData(COLOR_B, colAttribCapacity);
    colAttrib->addVtxData(COLOR_B, colAttribCapacity);

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
  MTHD_OVERRIDE(auto getGeometryInfo() const -> render::GeometryCreateInfo) {  // clang-format on
    render::GeometryCreateInfo info;

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

private:
  GeometryDataPtr<TVertexDataType> data_;
};

NAMESPACE_END(guides)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_GUIDES_AXIS_HPP
