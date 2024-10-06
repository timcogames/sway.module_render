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

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(procedurals)
NS_BEGIN(prims)

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
    data_ = std::make_shared<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>>(
        MAX_QUAD_RESERVE_VERTICES, MAX_QUAD_RESERVE_ELEMENTS);

    // clang-format off
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

  void setPosDataAttrib(f32_t zindex = 0.0F) {
    // dataAttribs_.pos->setData(0, math::vec3f_t(-0.5F, -0.5F, zindex).asDataPtr());
    // dataAttribs_.pos->setData(1, math::vec3f_t(+0.5F, -0.5F, zindex).asDataPtr());
    // dataAttribs_.pos->setData(2, math::vec3f_t(-0.5F, +0.5F, zindex).asDataPtr());
    // dataAttribs_.pos->setData(3, math::vec3f_t(+0.5F, +0.5F, zindex).asDataPtr());

    // data_->setTriElements(0, 2, 0, 1);
    // data_->setTriElements(3, 3, 2, 1);

    // dataAttribs_.pos->setData(0, math::vec3f_t(-0.5F, +0.5F, zindex).asDataPtr());
    // dataAttribs_.pos->setData(1, math::vec3f_t(-0.5F, -0.5F, zindex).asDataPtr());
    // dataAttribs_.pos->setData(2, math::vec3f_t(+0.5F, +0.5F, zindex).asDataPtr());
    // dataAttribs_.pos->setData(3, math::vec3f_t(+0.5F, -0.5F, zindex).asDataPtr());

    // data_->setTriElements(0, 0, 1, 2);
    // data_->setTriElements(3, 1, 3, 2);

    dataAttribs_.pos->setData(0, math::vec3f_t(-0.5F, +0.5F, zindex).asDataPtr());
    dataAttribs_.pos->setData(1, math::vec3f_t(-0.5F, -0.5F, zindex).asDataPtr());
    dataAttribs_.pos->setData(2, math::vec3f_t(+0.5F, +0.5F, zindex).asDataPtr());
    dataAttribs_.pos->setData(3, math::vec3f_t(+0.5F, -0.5F, zindex).asDataPtr());
  }

  void setPosDataAttrib(const std::array<f32_t, math::vec4f_t::DataElementCount_t> &coords, f32_t zindex = 0.0F) {
    dataAttribs_.pos->setData(0, math::vec3f_t(coords[core::detail::toBase(math::RectEdge::Enum::IDX_L)],
                                     coords[core::detail::toBase(math::RectEdge::Enum::IDX_B)], zindex)
                                     .asDataPtr());
    dataAttribs_.pos->setData(1, math::vec3f_t(coords[core::detail::toBase(math::RectEdge::Enum::IDX_R)],
                                     coords[core::detail::toBase(math::RectEdge::Enum::IDX_B)], zindex)
                                     .asDataPtr());
    dataAttribs_.pos->setData(2, math::vec3f_t(coords[core::detail::toBase(math::RectEdge::Enum::IDX_L)],
                                     coords[core::detail::toBase(math::RectEdge::Enum::IDX_T)], zindex)
                                     .asDataPtr());
    dataAttribs_.pos->setData(3, math::vec3f_t(coords[core::detail::toBase(math::RectEdge::Enum::IDX_R)],
                                     coords[core::detail::toBase(math::RectEdge::Enum::IDX_T)], zindex)
                                     .asDataPtr());
  }

  void setPosDataAttrib(const math::rect4f_t &pos, f32_t zindex = 0.0F) {
    dataAttribs_.pos->setData(0, math::vec3f_t(pos.getL(), pos.getB(), zindex).asDataPtr());
    dataAttribs_.pos->setData(1, math::vec3f_t(pos.getR(), pos.getB(), zindex).asDataPtr());
    dataAttribs_.pos->setData(2, math::vec3f_t(pos.getL(), pos.getT(), zindex).asDataPtr());
    dataAttribs_.pos->setData(3, math::vec3f_t(pos.getR(), pos.getT(), zindex).asDataPtr());
  }

  void setColDataAttrib(const math::col4f_t &col) {
    dataAttribs_.col->setData(0, col.asVec4().asDataPtr());
    dataAttribs_.col->setData(1, col.asVec4().asDataPtr());
    dataAttribs_.col->setData(2, col.asVec4().asDataPtr());
    dataAttribs_.col->setData(3, col.asVec4().asDataPtr());
  }

  void setTexDataAttrib(const math::rect4f_t &tex) {
    dataAttribs_.tex->setData(0, math::vec2f_t(tex.getL(), tex.getB()).asDataPtr());
    dataAttribs_.tex->setData(1, math::vec2f_t(tex.getR(), tex.getB()).asDataPtr());
    dataAttribs_.tex->setData(2, math::vec2f_t(tex.getL(), tex.getT()).asDataPtr());
    dataAttribs_.tex->setData(3, math::vec2f_t(tex.getR(), tex.getT()).asDataPtr());
  }

  [[nodiscard]]
  auto data() const -> std::shared_ptr<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>> {
    return data_;
  }

  MTHD_OVERRIDE(auto getVertexAttribs() const -> GeomVertexAttribSharedPtrMap_t) { return data_->getAttribs(); }

  MTHD_OVERRIDE(void getVertices(void *dst, u32_t start, u32_t end)) { data_->getVertices(dst, start, end); }

  MTHD_OVERRIDE(auto isIndexed() -> bool) { return true; }

  MTHD_OVERRIDE(auto mustBeRemapped() -> bool) { return remapping_; }

  MTHD_OVERRIDE(void setRemap(bool val)) { remapping_ = val; }

private:
  GeomVertexAttribSet dataAttribs_;
  std::shared_ptr<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>> data_;
  bool remapping_;
};

NS_END()  // namespace prims
NS_END()  // namespace procedurals
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERAL_HPP
