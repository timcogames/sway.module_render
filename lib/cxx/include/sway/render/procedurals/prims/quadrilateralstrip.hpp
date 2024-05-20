#ifndef SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERALStripSTRIP_HPP
#define SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERALStripSTRIP_HPP

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

  QuadrilateralStrip(
      const std::initializer_list<gapi::VertexSemantic> &semantics, const math::size2i_t &subdivs = math::size2i_t(1))
      : numChunks_(subdivs.getW() + 1, subdivs.getH() + 1)
      , remapping_(false) {
    initialVtxData(subdivs.area());
    initialElmData();

    data_->useSemanticSet(semantics);
  }

  virtual ~QuadrilateralStrip() = default;

  void initialVtxData(u32_t area) {
    data_ = std::make_shared<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>>(
        MAX_QUAD_RESERVE_VERTICES * area, MAX_QUAD_RESERVE_ELEMENTS * area);

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
      if (y > 0) {
        data_->setData(offset, y * numChunks_.getY());
        offset += 1;
      }

      for (auto x = 0; x < numChunks_.getX(); x++) {
        data_->setData(0 + offset, (y * numChunks_.getY()) + x);
        data_->setData(1 + offset, ((y + 1) * numChunks_.getY()) + x);
        offset += 2;
      }

      if (y < numChunks_.getY() - 2) {
        data_->setData(offset, (((y + 1) * numChunks_.getY()) + (numChunks_.getX() - 1)));
        offset += 1;
      }
    }
  }

  void setPosDataAttrib(const math::rect4f_t &coords) {
    auto offset = 0;
    for (auto y = 0; y < numChunks_.getY(); y++) {
      for (auto x = 0; x < numChunks_.getX(); x++) {
        auto xratio = x / static_cast<f32_t>(numChunks_.getX() - 1);
        auto yratio = 1.0F - (y / static_cast<f32_t>(numChunks_.getY() - 1));

        auto xpos = coords.getL() + (xratio * coords.getW());
        auto ypos = coords.getT() + (yratio * coords.getH());

        dataAttribs_.pos->setData(offset, math::vec3f_t(xpos, ypos, 0.0F).asDataPtr());
        offset += 1;
      }
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
        dataAttribs_.tex->setData(offset, size.multiply({static_cast<f32_t>(x), static_cast<f32_t>(y)}).asDataPtr());
        offset += 1;
      }
    }
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
  math::vec2i_t numChunks_;
  bool remapping_;
};

NAMESPACE_END(prims)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERALStripSTRIP_HPP
