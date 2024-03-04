#ifndef SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_STRIP_HPP
#define SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_STRIP_HPP

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

#define QUAD_NUM_RESERVE_VERTICES 4

template <typename TVertexDataType>
class Plane_Strip : public Shape {
public:
  Plane_Strip(math::size2f_t size, const math::size2i_t &subdivisions)
      : data_(std::make_shared<GeometryIndexedVertexData<TVertexDataType>>(
            (subdivisions.getW() + 1) * (subdivisions.getH() + 1))) {
    // math::size2f_t sizeHalf = size / 2.0F;

    GeometryVertexAttribSet attribs = {
        .pos = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::POS, QUAD_NUM_RESERVE_VERTICES),
        .col = data_->template createVertexAttrib<math::vec4f_t>(gapi::VertexSemantic::COL, QUAD_NUM_RESERVE_VERTICES),
        .tex = data_->template createVertexAttrib<math::vec2f_t>(
            gapi::VertexSemantic::TEXCOORD_0, QUAD_NUM_RESERVE_VERTICES)};

    const auto cols = subdivisions.getW() + 1;
    const auto rows = subdivisions.getH() + 1;

    for (auto row = 0; row < rows; row++) {
      for (auto col = 0; col < cols; col++) {
        auto xRatio = col / (f32_t)(cols - 1);
        auto yRatio = 1.0F - (row / (f32_t)(rows - 1));

        auto xPosition = -0.1F /*MIN_POSITION*/ + (xRatio * 1.0F /*POSITION_RANGE*/);
        auto yPosition = -0.1F /*MIN_POSITION*/ + (yRatio * 1.0F /*POSITION_RANGE*/);

        attribs.pos->addVtxData({xPosition, yPosition, 0.0F});
        attribs.col->addVtxData(math::vec4f_t(0.0F, 0.0F, 0.0F, 1.0F));
        attribs.tex->addVtxData(math::vec2f_t(col * (1.0F / cols), row * (1.0F / rows)));
      }
    }

    for (auto row = 0; row < rows - 1; row++) {
      if (row > 0) {
        data_->addIdxData(row * rows);
      }

      for (auto col = 0; col < cols; col++) {
        data_->addIdxData((row * rows) + col);
        data_->addIdxData(((row + 1) * rows) + col);
      }

      if (row < rows - 2) {
        data_->addIdxData((((row + 1) * rows) + (cols - 1)));
      }
    }
  }

  ~Plane_Strip() = default;

  [[nodiscard]]
  auto getGeometryData() const -> GeometryDataPtr<TVertexDataType> {
    return data_;
  }

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
  MTHD_OVERRIDE(auto getGeometryInfo() -> GeometryCreateInfo) {  // clang-format on
    GeometryCreateInfo info;
    info.topology = gapi::TopologyType::TRIANGLE_STRIP;

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

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_STRIP_HPP
