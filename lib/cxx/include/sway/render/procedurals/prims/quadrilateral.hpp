#ifndef SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERAL_HPP
#define SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERAL_HPP

#include <sway/math.hpp>
#include <sway/render/geom/geomindexedvertexdata.hpp>
#include <sway/render/geom/geomvertexdata.hpp>
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
class Quadrilateral : public ShapeBase {
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
    data_ = std::make_shared<GeomIndexedVertexData<TVertexDataType, u32_t>>(reserve * numInstances_,
      Constants::MAX_QUAD_RESERVE_ELEMENTS * numInstances_);
    dataAttribs_ = (struct GeomVertexAttribSet) {
      .pos = data_->template createAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
      .col = data_->template createAttrib<math::vec4f_t>(gapi::VertexSemantic::COL),
      .tex = data_->template createAttrib<math::vec2f_t>(gapi::VertexSemantic::TEXCOORD_0)
    };  // clang-format on
  }

  void initialElmData(std::size_t reserve) {
    auto next = 0;
    for (auto i = 0, offset = 0; i < reserve * numInstances_; i += reserve, offset += 4) {
      data_->setTriElements(next, 0 + offset, 1 + offset, 2 + offset);
      next += 3;
      data_->setTriElements(next, 2 + offset, 3 + offset, 0 + offset);
      next += 3;
    }
  }

  void setColor(const math::col4f_t &col) { color_ = col; }

  void update(u32_t idx, const math::rect4f_t &rect, const math::col4f_t col) {
    dataAttribs_.pos->setData(0 + idx, math::vec3f_t(rect.getR(), rect.getT(), 0.0F).data());
    dataAttribs_.pos->setData(1 + idx, math::vec3f_t(rect.getR(), rect.getB(), 0.0F).data());
    dataAttribs_.pos->setData(2 + idx, math::vec3f_t(rect.getL(), rect.getB(), 0.0F).data());
    dataAttribs_.pos->setData(3 + idx, math::vec3f_t(rect.getL(), rect.getT(), 0.0F).data());

    dataAttribs_.col->setData(0 + idx, col.toVec4().data());
    dataAttribs_.col->setData(1 + idx, col.toVec4().data());
    dataAttribs_.col->setData(2 + idx, col.toVec4().data());
    dataAttribs_.col->setData(3 + idx, col.toVec4().data());
  }

  void update(u32_t idx, const math::rect4f_t &rect, const math::col4f_t &col, const math::rect4f_t &tex) {
    dataAttribs_.pos->setData(0 + idx, math::vec3f_t(rect.getR(), rect.getT(), 0.0F).data());
    dataAttribs_.pos->setData(1 + idx, math::vec3f_t(rect.getR(), rect.getB(), 0.0F).data());
    dataAttribs_.pos->setData(2 + idx, math::vec3f_t(rect.getL(), rect.getB(), 0.0F).data());
    dataAttribs_.pos->setData(3 + idx, math::vec3f_t(rect.getL(), rect.getT(), 0.0F).data());

    dataAttribs_.col->setData(0 + idx, col.toVec4().data());
    dataAttribs_.col->setData(1 + idx, col.toVec4().data());
    dataAttribs_.col->setData(2 + idx, col.toVec4().data());
    dataAttribs_.col->setData(3 + idx, col.toVec4().data());

    dataAttribs_.tex->setData(0 + idx, math::vec2f_t(tex.getR(), tex.getB()).data());
    dataAttribs_.tex->setData(1 + idx, math::vec2f_t(tex.getR(), tex.getT()).data());
    dataAttribs_.tex->setData(2 + idx, math::vec2f_t(tex.getL(), tex.getT()).data());
    dataAttribs_.tex->setData(3 + idx, math::vec2f_t(tex.getL(), tex.getB()).data());
  }

  [[nodiscard]]
  auto getGeometryData() const -> GeometryDataPtr<TVertexDataType> {
    return data_;
  }

  void useVertexSemanticSet(const std::initializer_list<gapi::VertexSemantic> &semantics) {
    data_->useSemanticSet(semantics);
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttribs() const -> std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>>) {  // clang-format on
    return data_->getAttribs();
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttrib(gapi::VertexSemantic semantic) const -> std::shared_ptr<GeomVertexAttribBase>) {  // clang-format on
    return data_->getAttrib(semantic);
  }

  // clang-format off
  MTHD_OVERRIDE(auto getGeometryInfo() -> GeometryCreateInfo) {  // clang-format on
    GeometryCreateInfo info;
    info.topology = gapi::TopologyType::TRIANGLE_LIST;
    info.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::STATIC;
    info.bo[Constants::IDX_VBO].desc.byteStride = sizeof(TVertexDataType);
    info.bo[Constants::IDX_VBO].desc.capacity = data_->getVtxSize();
    info.bo[Constants::IDX_VBO].data = data_->getVertices(0, data_->getVtxSize());

    info.bo[Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
    info.bo[Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
    info.bo[Constants::IDX_EBO].desc.capacity = data_->getElmSize();
    info.bo[Constants::IDX_EBO].data = data_->getElements();

    return info;
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertices(u32_t start, u32_t end) -> void *) {  // clang-format on
    return data_->getVertices(start, end);
  }

public:
  GeomVertexAttribSet dataAttribs_;
  std::shared_ptr<GeomIndexedVertexData<TVertexDataType, u32_t>> data_;
  u32_t numInstances_;
  math::col4f_t color_;
};

NAMESPACE_END(prims)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERAL_HPP
