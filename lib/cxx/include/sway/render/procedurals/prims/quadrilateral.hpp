#ifndef SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_HPP
#define SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_HPP

#include <sway/math.hpp>
#include <sway/render/geom/geomindexedvertexdata.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/geometryvertexattribset.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/shape.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(procedurals)
NAMESPACE_BEGIN(prims)

template <typename TVertexDataType>
class Quadrilateral : public Shape {
public:
  Quadrilateral(u32_t numInsts)
      : numInstances_(numInsts)
      , color_(COL4F_WHITE) {
    initialVtxData(Constants::MAX_QUAD_RESERVE_VERTICES);
    initialElmData(Constants::MAX_QUAD_RESERVE_ELEMENTS);
  }

  virtual ~Quadrilateral() = default;

  void initialVtxData(std::size_t reserve) {
    // clang-format off
    data_ = std::make_shared<GeomIndexedVertexData<TVertexDataType>>(reserve * numInstances_);
    dataAttribs_ = {
      .pos = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::POS, reserve),
      .col = data_->template createVertexAttrib<math::vec4f_t>(gapi::VertexSemantic::COL, reserve),
      .tex = data_->template createVertexAttrib<math::vec2f_t>(gapi::VertexSemantic::TEXCOORD_0, reserve)
    };  // clang-format on
  }

  void initialElmData(std::size_t reserve) {
    for (auto i = 0, offset = 0; i < reserve * numInstances_; i += reserve, offset += 4) {
      data_->setTriElements(0 + offset, 1 + offset, 2 + offset);
      data_->setTriElements(2 + offset, 3 + offset, 0 + offset);
    }
  }

  void setColor(const math::col4f_t &col) { color_ = col; }

  void build() {
    math::size2f_t halfSize = 1.0F / 2.0F;

    dataAttribs_.pos->setData(0, math::vec3f_t(-halfSize.getW(), -halfSize.getH(), 0.0F).data());
    dataAttribs_.pos->setData(1, math::vec3f_t(+halfSize.getW(), -halfSize.getH(), 0.0F).data());
    dataAttribs_.pos->setData(2, math::vec3f_t(-halfSize.getW(), +halfSize.getH(), 0.0F).data());
    dataAttribs_.pos->setData(3, math::vec3f_t(+halfSize.getW(), +halfSize.getH(), 0.0F).data());

    dataAttribs_.col->setData(0, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).data());
    dataAttribs_.col->setData(1, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).data());
    dataAttribs_.col->setData(2, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).data());
    dataAttribs_.col->setData(3, math::vec4f_t(1.0F, 1.0F, 1.0F, 1.0F).data());

    dataAttribs_.tex->setData(0, math::vec2f_t(0.0F, 1.0F).data());
    dataAttribs_.tex->setData(1, math::vec2f_t(1.0F, 1.0F).data());
    dataAttribs_.tex->setData(2, math::vec2f_t(0.0F, 0.0F).data());
    dataAttribs_.tex->setData(3, math::vec2f_t(1.0F, 0.0F).data());

    data_->setTriElements(0, 2, 1);
    data_->setTriElements(1, 2, 3);
  }

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
    info.topology = gapi::TopologyType::TRIANGLE_LIST;
    info.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::STATIC;
    info.bo[Constants::IDX_VBO].desc.byteStride = sizeof(TVertexDataType);
    info.bo[Constants::IDX_VBO].desc.capacity = data_->getVtxSize();
    info.bo[Constants::IDX_VBO].data = data_->getVertices();

    info.bo[Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
    info.bo[Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
    info.bo[Constants::IDX_EBO].desc.capacity = data_->getElmSize();
    info.bo[Constants::IDX_EBO].data = data_->getElements();

    return info;
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertices() -> void *) {  // clang-format on
    return data_->getVtxRawdata();
  }

private:
  GeometryVertexAttribSet dataAttribs_;
  GeometryDataPtr<TVertexDataType> data_;
  u32_t numInstances_;
  math::col4f_t color_;
};

NAMESPACE_END(prims)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_HPP
