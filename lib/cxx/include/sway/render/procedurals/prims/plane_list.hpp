#ifndef SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_LIST_HPP
#define SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_LIST_HPP

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

#define QUAD_NUM_RESERVE_VERTICES 4

template <typename TVertexDataType>
class Plane_List : public Shape {
public:
  Plane_List(math::size2f_t size, const math::size2i_t &subdivisions)
      : data_(std::make_shared<GeometryIndexedVertexData<TVertexDataType>>(subdivisions.getW() * subdivisions.getH())) {
    // math::size2f_t sizeHalf = size / 2.0F;

    GeometryVertexAttribSet attribs = {
        .pos = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::POS, QUAD_NUM_RESERVE_VERTICES),
        .col = data_->template createVertexAttrib<math::vec4f_t>(gapi::VertexSemantic::COL, QUAD_NUM_RESERVE_VERTICES),
        .tex = data_->template createVertexAttrib<math::vec2f_t>(
            gapi::VertexSemantic::TEXCOORD_0, QUAD_NUM_RESERVE_VERTICES)};

    //  0-------1-------2-------3
    //  |     / |     / |     / |
    //  |   /   |   /   |   /   |
    //  | /     | /     | /     |
    //  4-------5-------6-------7
    //  |     / |     / |     / |
    //  |   /   |   /   |   /   |
    //  | /     | /     | /     |
    //  8-------9-------10------11
    //  |     / |     / |     / |
    //  |   /   |   /   |   /   |
    //  | /     | /     | /     |
    //  12------13------14------15

    const auto cols = subdivisions.getW();
    const auto rows = subdivisions.getH();

    for (auto row = 0; row < rows; row++) {
      for (auto col = 0; col < cols; col++) {
        attribs.pos->addVtxData({(float)col * 0.5F, (float)row * 0.5F, 0.0F});
        attribs.col->addVtxData(math::vec4f_t(0.0F, 0.0F, 0.0F, 1.0F));
        attribs.tex->addVtxData(math::vec2f_t(col * (1.0F / cols), row * (1.0F / rows)));
      }
    }

    for (auto row = 0; row < rows - 1; row++) {
      for (auto col = 0; col < cols - 1; col++) {

        auto topLeft = row * rows + col;
        auto stride = cols;

        auto TL = topLeft;
        auto BL = topLeft + stride;
        auto TR = topLeft + 1;
        auto BR = topLeft + stride + 1;

        data_->addTriIndices(TL, BL, TR);
        data_->addTriIndices(BL, BR, TR);
      }
    }
  }

  ~Plane_List() = default;

  [[nodiscard]]
  auto getGeometryData() const -> GeometryDataPtr<TVertexDataType> {
    return data_;
  }

  template <std::size_t TSize>
  void useVertexSemanticSet(std::array<sway::gapi::VertexSemantic, TSize> &arr) {
    data_->useVertexSemanticSet(arr);
  }

  MTHD_OVERRIDE(auto getVertexAttribs() const -> VertexAttribMap_t) { return data_->getAttribs(); }

  MTHD_OVERRIDE(auto getVertexAttrib(gapi::VertexSemantic semantic) const -> VertexAttribPtr_t) { return data_->getAttrib(semantic); }

  MTHD_OVERRIDE(auto getGeometryInfo() -> GeometryCreateInfo) {
    GeometryCreateInfo info;

    info.topology = gapi::TopologyType::TRIANGLE_LIST;
    info.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::STATIC;
    info.bo[Constants::IDX_VBO].desc.byteStride = sizeof(TVertexDataType);
    info.bo[Constants::IDX_VBO].desc.capacity = data_->getVtxCount();
    info.bo[Constants::IDX_VBO].data = data_->getVtxRawdata();

    info.bo[Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
    info.bo[Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
    info.bo[Constants::IDX_EBO].desc.capacity = data_->getIdxCount();
    info.bo[Constants::IDX_EBO].data = data_->getIndices().data();

    return info;
  }

  MTHD_OVERRIDE(auto getVertices() -> void *) { return data_->getVtxRawdata(); }

private:
  GeometryDataPtr<TVertexDataType> data_;
};

NAMESPACE_END(prims)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_LIST_HPP
