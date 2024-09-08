#ifndef SWAY_RENDER_PROCEDURALS_GUIDES_LINE_HPP
#define SWAY_RENDER_PROCEDURALS_GUIDES_LINE_HPP

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
NAMESPACE_BEGIN(guides)

class Line : public ShapeBase {
public:
  using VtxDataType_t = math::VertexColor;
  using IdxDataType_t = u32_t;

  static constexpr std::size_t MAX_LINE_RESERVE_VERTICES{2};
  static constexpr std::size_t MAX_LINE_RESERVE_ELEMENTS{0};

  Line()
      : remapping_(false) {
    initialVtxData();

    data_->useSemanticSet({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  }

  virtual ~Line() = default;

  void initialVtxData() {
    data_ = std::make_shared<GeomVertexData<VtxDataType_t>>(MAX_LINE_RESERVE_VERTICES);

    // clang-format off
    dataAttribs_ = (struct GeomVertexAttribSet) {
      .pos = data_->template createAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
      .col = data_->template createAttrib<math::vec4f_t>(gapi::VertexSemantic::COL),
      .tex = nullptr
    };
    // clang-format on
  }

  void setPosDataAttrib(math::vec3f_t start, math::vec3f_t end) {
    dataAttribs_.pos->setData(0, start.asDataPtr());
    dataAttribs_.pos->setData(1, end.asDataPtr());
  }

  void setColDataAttrib(const math::col4f_t &col) {
    dataAttribs_.col->setData(0, col.asVec4().asDataPtr());
    dataAttribs_.col->setData(1, col.asVec4().asDataPtr());
  }

  [[nodiscard]]
  auto data() const -> std::shared_ptr<GeomVertexData<VtxDataType_t>> {
    return data_;
  }

  MTHD_OVERRIDE(auto getVertexAttribs() const->std::map<gapi::VertexSemantic, GeomVertexAttribBase::SharedPtr_t>) {
    return data_->getAttribs();
  }

  MTHD_OVERRIDE(void getVertices(void *dst, u32_t start, u32_t end)) { data_->getVertices(dst, start, end); }

  MTHD_OVERRIDE(auto isIndexed() -> bool) { return false; }

  MTHD_OVERRIDE(auto mustBeRemapped() -> bool) { return remapping_; }

  MTHD_OVERRIDE(void setRemap(bool val)) { remapping_ = val; }

private:
  GeomVertexAttribSet dataAttribs_;
  std::shared_ptr<GeomVertexData<VtxDataType_t>> data_;
  bool remapping_;
};

NAMESPACE_END(guides)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_GUIDES_LINE_HPP
