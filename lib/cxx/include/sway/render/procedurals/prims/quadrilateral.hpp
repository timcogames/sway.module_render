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
  using VtxDataType_t = TVertexDataType;
  using IdxDataType_t = u32_t;

  static constexpr std::size_t MAX_QUAD_RESERVE_VERTICES{4};
  static constexpr std::size_t MAX_QUAD_RESERVE_ELEMENTS{6};

  Quadrilateral(const std::initializer_list<gapi::VertexSemantic> &semantics)
      : remapping_(false) {
    initialVtxData();
    initialElmData();

    data_->useSemanticSet(semantics);
  }

  virtual ~Quadrilateral() = default;

  void initialVtxData() {
    // clang-format off
    data_ = std::make_shared<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>>(
      MAX_QUAD_RESERVE_VERTICES,
      MAX_QUAD_RESERVE_ELEMENTS
    );

    dataAttribs_ = (struct GeomVertexAttribSet) {
      .pos = data_->template createAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
      .col = data_->template createAttrib<math::vec4f_t>(gapi::VertexSemantic::COL),
      .tex = data_->template createAttrib<math::vec2f_t>(gapi::VertexSemantic::TEXCOORD_0)
    };
    // clang-format on
  }

  void initialElmData() {
    data_->setTriElements(0 /* offset */, 0, 2, 1);
    data_->setTriElements(3 /* offset */, 1, 2, 3);
  }

  void setPosDataAttrib(const math::rect4f_t &pos) {
    dataAttribs_.pos->setData(0, math::vec3f_t(pos.getL(), pos.getT(), 0.0F).data());
    dataAttribs_.pos->setData(1, math::vec3f_t(pos.getR(), pos.getT(), 0.0F).data());
    dataAttribs_.pos->setData(2, math::vec3f_t(pos.getL(), pos.getB(), 0.0F).data());
    dataAttribs_.pos->setData(3, math::vec3f_t(pos.getR(), pos.getB(), 0.0F).data());
  }

  void setColDataAttrib(const math::col4f_t &col) {
    dataAttribs_.col->setData(0, col.toVec4().data());
    dataAttribs_.col->setData(1, col.toVec4().data());
    dataAttribs_.col->setData(2, col.toVec4().data());
    dataAttribs_.col->setData(3, col.toVec4().data());
  }

  void setTexDataAttrib(const math::rect4f_t &tex) {
    dataAttribs_.tex->setData(0, math::vec2f_t(tex.getL(), tex.getT()).data());
    dataAttribs_.tex->setData(1, math::vec2f_t(tex.getR(), tex.getT()).data());
    dataAttribs_.tex->setData(2, math::vec2f_t(tex.getL(), tex.getB()).data());
    dataAttribs_.tex->setData(3, math::vec2f_t(tex.getR(), tex.getB()).data());
  }

  [[nodiscard]]
  auto data() const -> std::shared_ptr<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>> {
    return data_;
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttribs() const -> std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>>) {  // clang-format on
    return data_->getAttribs();
  }

  MTHD_OVERRIDE(void getVertices(void *dst, u32_t start, u32_t end)) { data_->getVertices(dst, start, end); }

  // clang-format off
  MTHD_OVERRIDE(auto isIndexed() -> bool) {  // clang-format on
    return true;
  }

  // clang-format off
  MTHD_OVERRIDE(auto mustBeRemapped() -> bool) {  // clang-format on
    return remapping_;
  }

  MTHD_OVERRIDE(void setRemap(bool val)) { remapping_ = val; }

private:
  GeomVertexAttribSet dataAttribs_;
  std::shared_ptr<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>> data_;
  bool remapping_;
};

NAMESPACE_END(prims)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERAL_HPP
