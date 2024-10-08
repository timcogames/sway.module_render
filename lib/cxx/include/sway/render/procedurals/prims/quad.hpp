#ifndef SWAY_RENDER_PROCEDURALS_PRIMS_QUAD_HPP
#define SWAY_RENDER_PROCEDURALS_PRIMS_QUAD_HPP

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
class Quad : public ShapeBase {
public:
  using VtxDataType_t = TVertexDataType;

  static constexpr std::size_t MAX_QUAD_RESERVE_VERTICES{4};

  Quad(const std::initializer_list<gapi::VertexSemantic> &semantics)
      : remapping_(false) {
    initialVtxData();

    data_->useSemanticSet(semantics);
  }

  virtual ~Quad() = default;

  void initialVtxData() {
    data_ = std::make_shared<GeomVertexData<VtxDataType_t>>(MAX_QUAD_RESERVE_VERTICES);

    // clang-format off
    dataAttribs_ = (struct GeomVertexAttribSet) {
      .pos = data_->template createAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
      .col = data_->template createAttrib<math::vec4f_t>(gapi::VertexSemantic::COL),
      .tex = data_->template createAttrib<math::vec2f_t>(gapi::VertexSemantic::TEXCOORD_0)
    };
    // clang-format on
  }

  void setPosDataAttrib(f32_t zindex) {
    // dataAttribs_.pos->setData(0, math::vec3f_t(-0.5f, -0.5f, zindex).asDataPtr());
    // dataAttribs_.pos->setData(1, math::vec3f_t(+0.5f, -0.5f, zindex).asDataPtr());
    // dataAttribs_.pos->setData(2, math::vec3f_t(+0.5f, +0.5f, zindex).asDataPtr());

    // dataAttribs_.pos->setData(3, math::vec3f_t(+0.5f, +0.5f, zindex).asDataPtr());
    // dataAttribs_.pos->setData(4, math::vec3f_t(-0.5f, +0.5f, zindex).asDataPtr());
    // dataAttribs_.pos->setData(5, math::vec3f_t(-0.5f, -0.5f, zindex).asDataPtr());

    dataAttribs_.pos->setData(0, math::vec3f_t(-100.5f, +100.5f, zindex).asDataPtr());
    dataAttribs_.pos->setData(1, math::vec3f_t(-100.5f, -100.5f, zindex).asDataPtr());
    dataAttribs_.pos->setData(2, math::vec3f_t(+100.5f, +100.5f, zindex).asDataPtr());
    dataAttribs_.pos->setData(3, math::vec3f_t(+100.5f, -100.5f, zindex).asDataPtr());
  }

  void setColDataAttrib() {
    // dataAttribs_.col->setData(0, COL4F_RED.asVec4().asDataPtr());
    // dataAttribs_.col->setData(1, COL4F_RED.asVec4().asDataPtr());
    // dataAttribs_.col->setData(2, COL4F_RED.asVec4().asDataPtr());

    // dataAttribs_.col->setData(3, COL4F_RED.asVec4().asDataPtr());
    // dataAttribs_.col->setData(4, COL4F_RED.asVec4().asDataPtr());
    // dataAttribs_.col->setData(5, COL4F_RED.asVec4().asDataPtr());

    dataAttribs_.col->setData(0, COL4F_RED.asVec4().asDataPtr());
    dataAttribs_.col->setData(1, COL4F_RED.asVec4().asDataPtr());
    dataAttribs_.col->setData(2, COL4F_RED.asVec4().asDataPtr());
    dataAttribs_.col->setData(3, COL4F_RED.asVec4().asDataPtr());
  }

  void setTexDataAttrib() {
    // dataAttribs_.tex->setData(0, math::vec2f_t(0.0f, 0.0f).asDataPtr());
    // dataAttribs_.tex->setData(1, math::vec2f_t(1.0f, 1.0f).asDataPtr());
    // dataAttribs_.tex->setData(2, math::vec2f_t(0.0f, 1.0f).asDataPtr());

    // dataAttribs_.tex->setData(3, math::vec2f_t(0.0f, 0.0f).asDataPtr());
    // dataAttribs_.tex->setData(4, math::vec2f_t(1.0f, 0.0f).asDataPtr());
    // dataAttribs_.tex->setData(5, math::vec2f_t(1.0f, 1.0f).asDataPtr());

    dataAttribs_.tex->setData(0, math::vec2f_t(0.0f, 1.0f).asDataPtr());
    dataAttribs_.tex->setData(1, math::vec2f_t(0.0f, 0.0f).asDataPtr());
    dataAttribs_.tex->setData(2, math::vec2f_t(1.0f, 1.0f).asDataPtr());
    dataAttribs_.tex->setData(3, math::vec2f_t(1.0f, 0.0f).asDataPtr());
  }

  [[nodiscard]]
  auto data() const -> std::shared_ptr<GeomVertexData<VtxDataType_t>> {
    return data_;
  }

  MTHD_OVERRIDE(auto getVertexAttribs() const -> GeomVertexAttribSharedPtrMap_t) { return data_->getAttribs(); }

  MTHD_OVERRIDE(void getVertices(void *dst, u32_t start, u32_t end)) { data_->getVertices(dst, start, end); }

  MTHD_OVERRIDE(auto isIndexed() -> bool) { return false; }

  MTHD_OVERRIDE(auto mustBeRemapped() -> bool) { return remapping_; }

  MTHD_OVERRIDE(void setRemap(bool val)) { remapping_ = val; }

private:
  GeomVertexAttribSet dataAttribs_;
  std::shared_ptr<GeomVertexData<VtxDataType_t>> data_;
  bool remapping_;
};

NS_END()  // namespace prims
NS_END()  // namespace procedurals
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_QUAD_HPP
