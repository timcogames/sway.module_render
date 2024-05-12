#ifndef SWAY_RENDER_PROCEDURALS_GUIDES_AXIS_HPP
#define SWAY_RENDER_PROCEDURALS_GUIDES_AXIS_HPP

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
NAMESPACE_BEGIN(guides)

template <typename TVertexDataType>
using GeometryDataPtr = std::shared_ptr<GeometryIndexedVertexData<TVertexDataType>>;

template <typename TVertexDataType>
class Axis : public ShapeBase {
public:
  using VtxDataType_t = TVertexDataType;
  using IdxDataType_t = u32_t;

  // static constexpr std::size_t MAX_AXIS_RESERVE_VERTICES{12};
  static constexpr std::size_t MAX_AXIS_RESERVE_VERTICES{8};
  // static constexpr std::size_t MAX_AXIS_RESERVE_ELEMENTS{18};
  static constexpr std::size_t MAX_AXIS_RESERVE_ELEMENTS{12};

  Axis(const std::initializer_list<gapi::VertexSemantic> &semantics)
      : data_(std::make_shared<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>>(
            MAX_AXIS_RESERVE_VERTICES, MAX_AXIS_RESERVE_ELEMENTS)) {

    // clang-format off
    dataAttribs_ = (struct GeomVertexAttribSet) {
      .pos = data_->template createAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
      .col = data_->template createAttrib<math::vec4f_t>(gapi::VertexSemantic::COL),
      .tex = nullptr
    };
    // clang-format on

    // X axis
    dataAttribs_.pos->setData(0 + 0, math::vec3f_t(+0.0F, +0.0F, +0.0F).asDataPtr());
    dataAttribs_.pos->setData(1 + 0, math::vec3f_t(+1.0F, +0.0F, +0.0F).asDataPtr());
    dataAttribs_.pos->setData(2 + 0, math::vec3f_t(+0.9F, +0.1F, +0.0F).asDataPtr());
    dataAttribs_.pos->setData(3 + 0, math::vec3f_t(+0.9F, -0.1F, +0.0F).asDataPtr());
    // Y axis
    dataAttribs_.pos->setData(0 + 4, math::vec3f_t(+0.0F, +0.0F, +0.0F).asDataPtr());
    dataAttribs_.pos->setData(1 + 4, math::vec3f_t(+0.0F, +1.0F, +0.0F).asDataPtr());
    dataAttribs_.pos->setData(2 + 4, math::vec3f_t(+0.1F, +0.9F, +0.0F).asDataPtr());
    dataAttribs_.pos->setData(3 + 4, math::vec3f_t(-0.1F, +0.9F, +0.0F).asDataPtr());
    // Z axis
    // dataAttribs_.pos->setData(0 + 8, math::vec3f_t(+0.0F, +0.0F, +0.0F).asDataPtr());
    // dataAttribs_.pos->setData(1 + 8, math::vec3f_t(+0.0F, +0.0F, +1.0F).asDataPtr());
    // dataAttribs_.pos->setData(2 + 8, math::vec3f_t(+0.1F, +0.0F, +0.9F).asDataPtr());
    // dataAttribs_.pos->setData(3 + 8, math::vec3f_t(-0.1F, +0.0F, +0.9F).asDataPtr());

    // X axis
    dataAttribs_.col->setData(0 + 0, COL4F_RED.asVec4().asDataPtr());
    dataAttribs_.col->setData(1 + 0, COL4F_RED.asVec4().asDataPtr());
    dataAttribs_.col->setData(2 + 0, COL4F_RED.asVec4().asDataPtr());
    dataAttribs_.col->setData(3 + 0, COL4F_RED.asVec4().asDataPtr());
    // Y axis
    dataAttribs_.col->setData(0 + 4, COL4F_GREEN.asVec4().asDataPtr());
    dataAttribs_.col->setData(1 + 4, COL4F_GREEN.asVec4().asDataPtr());
    dataAttribs_.col->setData(2 + 4, COL4F_GREEN.asVec4().asDataPtr());
    dataAttribs_.col->setData(3 + 4, COL4F_GREEN.asVec4().asDataPtr());
    // Z axis
    // dataAttribs_.col->setData(0 + 8, COL4F_BLUE.asVec4().asDataPtr());
    // dataAttribs_.col->setData(1 + 8, COL4F_BLUE.asVec4().asDataPtr());
    // dataAttribs_.col->setData(2 + 8, COL4F_BLUE.asVec4().asDataPtr());
    // dataAttribs_.col->setData(3 + 8, COL4F_BLUE.asVec4().asDataPtr());

    // X axis
    data_->setData(0, 0);
    data_->setData(1, 1);
    data_->setData(2, 1);
    data_->setData(3, 2);
    data_->setData(4, 1);
    data_->setData(5, 3);
    // Y axis
    data_->setData(6, 4);
    data_->setData(7, 5);
    data_->setData(8, 5);
    data_->setData(9, 6);
    data_->setData(10, 5);
    data_->setData(11, 7);
    // Z axis
    // data_->setData(12, 8);
    // data_->setData(13, 9);
    // data_->setData(14, 9);
    // data_->setData(15, 10);
    // data_->setData(16, 9);
    // data_->setData(17, 11);

    data_->useSemanticSet(semantics);
  }

  ~Axis() = default;

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
    return false;
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

NAMESPACE_END(guides)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_GUIDES_AXIS_HPP
