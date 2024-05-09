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

template <typename TVertexDataType>
class Line : public ShapeBase {
public:
  using VtxDataType_t = TVertexDataType;
  using IdxDataType_t = u32_t;

  static constexpr std::size_t MAX_QUAD_RESERVE_VERTICES{2};
  static constexpr std::size_t MAX_QUAD_RESERVE_ELEMENTS{0};

  Line(const std::initializer_list<gapi::VertexSemantic> &semantics) {
    initialVtxData();

    data_->useSemanticSet(semantics);
  }

  virtual ~Line() = default;

  void initialVtxData() {
    // clang-format off
    data_ = std::make_shared<GeomVertexData<VtxDataType_t>>(
      2//MAX_QUAD_RESERVE_VERTICES
    );

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

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttribs() const -> std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>>) {  // clang-format on
    return data_->getAttribs();
  }

  MTHD_OVERRIDE(void getVertices(void *dst, u32_t start, u32_t end)) { data_->getVertices(dst, start, end); }

  MTHD_OVERRIDE(auto isIndexed()->bool) { return false; }

private:
  GeomVertexAttribSet dataAttribs_;
  std::shared_ptr<GeomVertexData<VtxDataType_t>> data_;
};

NAMESPACE_END(guides)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_GUIDES_LINE_HPP
