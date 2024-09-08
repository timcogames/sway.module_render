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

class Axis : public ShapeBase {
public:
  using VtxDataType_t = math::VertexColor;
  using IdxDataType_t = u32_t;

  // static constexpr std::size_t MAX_AXIS_RESERVE_VERTICES{12};
  static constexpr std::size_t MAX_AXIS_RESERVE_VERTICES{8};
  // static constexpr std::size_t MAX_AXIS_RESERVE_ELEMENTS{18};
  static constexpr std::size_t MAX_AXIS_RESERVE_ELEMENTS{12};

  Axis()
      : data_(std::make_shared<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>>(
            MAX_AXIS_RESERVE_VERTICES, MAX_AXIS_RESERVE_ELEMENTS)) {

    // clang-format off
    dataAttribs_ = (struct GeomVertexAttribSet) {
      .pos = data_->template createAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
      .col = data_->template createAttrib<math::vec4f_t>(gapi::VertexSemantic::COL),
      .tex = nullptr
    };
    // clang-format on

    core::detail::EnumClassBitset<math::Axis> axises;
    axises.set(math::Axis::RIGHT);
    axises.set(math::Axis::UP);

    auto offsetVtxes = 0, offsetIdxes = 0;

    if (axises.has(math::Axis::RIGHT)) {  // X axis
      dataAttribs_.pos->setData(0 + offsetVtxes, math::vec3f_t(+0.0F, +0.0F, +0.0F).asDataPtr());
      dataAttribs_.pos->setData(1 + offsetVtxes, math::vec3f_t(+1.0F, +0.0F, +0.0F).asDataPtr());
      dataAttribs_.pos->setData(2 + offsetVtxes, math::vec3f_t(+0.9F, +0.1F, +0.0F).asDataPtr());
      dataAttribs_.pos->setData(3 + offsetVtxes, math::vec3f_t(+0.9F, -0.1F, +0.0F).asDataPtr());

      dataAttribs_.col->setData(0 + offsetVtxes, COL4F_RED.asVec4().asDataPtr());
      dataAttribs_.col->setData(1 + offsetVtxes, COL4F_RED.asVec4().asDataPtr());
      dataAttribs_.col->setData(2 + offsetVtxes, COL4F_RED.asVec4().asDataPtr());
      dataAttribs_.col->setData(3 + offsetVtxes, COL4F_RED.asVec4().asDataPtr());

      offsetVtxes += 4;

      data_->setData(0 + offsetIdxes, 0);
      data_->setData(1 + offsetIdxes, 1);
      data_->setData(2 + offsetIdxes, 1);
      data_->setData(3 + offsetIdxes, 2);
      data_->setData(4 + offsetIdxes, 1);
      data_->setData(5 + offsetIdxes, 3);

      offsetIdxes += 6;
    }

    if (axises.has(math::Axis::UP)) {  // Y axis
      dataAttribs_.pos->setData(0 + offsetVtxes, math::vec3f_t(+0.0F, +0.0F, +0.0F).asDataPtr());
      dataAttribs_.pos->setData(1 + offsetVtxes, math::vec3f_t(+0.0F, +1.0F, +0.0F).asDataPtr());
      dataAttribs_.pos->setData(2 + offsetVtxes, math::vec3f_t(+0.1F, +0.9F, +0.0F).asDataPtr());
      dataAttribs_.pos->setData(3 + offsetVtxes, math::vec3f_t(-0.1F, +0.9F, +0.0F).asDataPtr());

      dataAttribs_.col->setData(0 + offsetVtxes, COL4F_GREEN.asVec4().asDataPtr());
      dataAttribs_.col->setData(1 + offsetVtxes, COL4F_GREEN.asVec4().asDataPtr());
      dataAttribs_.col->setData(2 + offsetVtxes, COL4F_GREEN.asVec4().asDataPtr());
      dataAttribs_.col->setData(3 + offsetVtxes, COL4F_GREEN.asVec4().asDataPtr());

      offsetVtxes += 4;

      data_->setData(0 + offsetIdxes, 4);
      data_->setData(1 + offsetIdxes, 5);
      data_->setData(2 + offsetIdxes, 5);
      data_->setData(3 + offsetIdxes, 6);
      data_->setData(4 + offsetIdxes, 5);
      data_->setData(5 + offsetIdxes, 7);

      offsetIdxes += 6;
    }

    if (axises.has(math::Axis::FORWARD)) {  // Z axis
      dataAttribs_.pos->setData(0 + offsetVtxes, math::vec3f_t(+0.0F, +0.0F, +0.0F).asDataPtr());
      dataAttribs_.pos->setData(1 + offsetVtxes, math::vec3f_t(+0.0F, +0.0F, +1.0F).asDataPtr());
      dataAttribs_.pos->setData(2 + offsetVtxes, math::vec3f_t(+0.1F, +0.0F, +0.9F).asDataPtr());
      dataAttribs_.pos->setData(3 + offsetVtxes, math::vec3f_t(-0.1F, +0.0F, +0.9F).asDataPtr());

      dataAttribs_.col->setData(0 + offsetVtxes, COL4F_BLUE.asVec4().asDataPtr());
      dataAttribs_.col->setData(1 + offsetVtxes, COL4F_BLUE.asVec4().asDataPtr());
      dataAttribs_.col->setData(2 + offsetVtxes, COL4F_BLUE.asVec4().asDataPtr());
      dataAttribs_.col->setData(3 + offsetVtxes, COL4F_BLUE.asVec4().asDataPtr());

      offsetVtxes += 4;

      data_->setData(0 + offsetIdxes, 8);
      data_->setData(1 + offsetIdxes, 9);
      data_->setData(2 + offsetIdxes, 9);
      data_->setData(3 + offsetIdxes, 10);
      data_->setData(4 + offsetIdxes, 9);
      data_->setData(5 + offsetIdxes, 11);

      offsetIdxes += 6;
    }

    data_->useSemanticSet({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});
  }

  ~Axis() = default;

  [[nodiscard]]
  auto data() const -> std::shared_ptr<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>> {
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
  std::shared_ptr<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>> data_;
  bool remapping_;
};

NAMESPACE_END(guides)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_GUIDES_AXIS_HPP
