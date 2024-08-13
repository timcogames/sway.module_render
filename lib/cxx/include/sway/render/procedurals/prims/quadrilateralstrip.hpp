#ifndef SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERALSTRIP_HPP
#define SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERALSTRIP_HPP

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
class QuadrilateralStrip : public ShapeBase {
public:
  using VtxDataType_t = TVertexDataType;
  using IdxDataType_t = u32_t;

  static constexpr std::size_t MAX_QUAD_RESERVE_VERTICES{4};
  static constexpr std::size_t MAX_QUAD_RESERVE_ELEMENTS{6};

  QuadrilateralStrip(const std::initializer_list<gapi::VertexSemantic> &semantics, const math::size2i_t &subdivs)
      : numChunks_(subdivs.getW() + 1, subdivs.getH() + 1)
      , area_(subdivs.area())
      , remapping_(false) {
    initialVtxData();
    initialElmData();

    data_->useSemanticSet(semantics);
  }

  virtual ~QuadrilateralStrip() = default;

  auto getReserveVerts() const { return MAX_QUAD_RESERVE_VERTICES * (area_ > 1 ? 4 : 1); }

  auto getReserveElems() const { return MAX_QUAD_RESERVE_ELEMENTS * (area_); }

  void initialVtxData() {
    data_ = std::make_shared<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>>(getReserveVerts(), getReserveElems());

    // clang-format off
    dataAttribs_ = (struct GeomVertexAttribSet) {
      .pos = data_->template createAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
      .col = data_->template createAttrib<math::vec4f_t>(gapi::VertexSemantic::COL),
      .tex = data_->template createAttrib<math::vec2f_t>(gapi::VertexSemantic::TEXCOORD_0)
    };
    // clang-format on
  }

  void initialElmData() {
    auto offset = 0;
    for (auto y = 0; y < numChunks_.getY() - 1; y++) {
      for (auto x = 0; x < numChunks_.getX() - 1; x++) {

        auto topLeft = y * numChunks_.getY() + x;
        auto stride = numChunks_.getX();

        auto TL = topLeft;
        auto BL = topLeft + stride;
        auto TR = topLeft + 1;
        auto BR = topLeft + stride + 1;

        data_->setTriElements(offset, TL, TR, BL);
        offset += 3;

        data_->setTriElements(offset, TR, BL, BR);
        offset += 3;
      }
    }
  }

  void setPosDataAttrib(const math::rect4f_t &coords) {
    auto offset = 0;

    for (auto i = 0; i < numChunks_.getX() * numChunks_.getY(); i++) {
      auto x = i % numChunks_.getX();
      auto y = i / numChunks_.getX();
      auto xratio = f32_t(x) / f32_t(numChunks_.getX() - 1);
      auto yratio = 1.0F - (f32_t(y) / f32_t(numChunks_.getY() - 1));
      auto xpos = coords.getL() + (xratio * coords.getW());
      auto ypos = coords.getT() + (yratio * coords.getH());

      if (area_ > 1 && x == 1) {
        xpos = xpos - 0.2F;
      }

      if (area_ > 1 && x == 2) {
        xpos = xpos + 0.2F;
      }

      auto data = math::vec3f_t(xpos, ypos, 0.0F);
      dataAttribs_.pos->setData(offset, data.asDataPtr());
      offset += 1;
    }
  }

  void setColDataAttrib(const math::col4f_t &col) {
    auto offset = 0;
    for (auto y = 0; y < numChunks_.getY(); y++) {
      for (auto x = 0; x < numChunks_.getX(); x++) {
        dataAttribs_.col->setData(offset, col.asVec4().asDataPtr());
        offset += 1;
      }
    }
  }

  void setTexDataAttrib(const math::rect4f_t &tex) {
    auto offset = 0;
    for (auto y = 0; y < numChunks_.getY(); y++) {
      for (auto x = 0; x < numChunks_.getX(); x++) {
        auto size = math::Texel::convFromTexCoords<math::vec2f_t>(numChunks_.getX() - 1, numChunks_.getY() - 1);
        auto data = size.multiply({static_cast<f32_t>(x), static_cast<f32_t>(y)});
        dataAttribs_.tex->setData(offset, data.asDataPtr());
        offset += 1;
      }
    }
  }

  [[nodiscard]]
  auto data() const -> std::shared_ptr<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>> {
    return data_;
  }

  MTHD_OVERRIDE(auto getVertexAttribs() const->std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>>) {
    return data_->getAttribs();
  }

  MTHD_OVERRIDE(void getVertices(void *dst, u32_t start, u32_t end)) { data_->getVertices(dst, start, end); }

  MTHD_OVERRIDE(auto isIndexed() -> bool) { return true; }

  MTHD_OVERRIDE(auto mustBeRemapped() -> bool) { return remapping_; }

  MTHD_OVERRIDE(void setRemap(bool val)) { remapping_ = val; }

private:
  GeomVertexAttribSet dataAttribs_;
  std::shared_ptr<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>> data_;
  math::vec2i_t numChunks_;
  u32_t area_;
  bool remapping_;
};

NAMESPACE_END(prims)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERALSTRIP_HPP
