#ifndef SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERALSTRIP_HPP
#define SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERALSTRIP_HPP

#include <sway/math.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/geom/geomcreateinfo.hpp>
#include <sway/render/geom/geomindexedvertexdata.hpp>
#include <sway/render/geom/geomvertexattribset.hpp>
#include <sway/render/geom/geomvertexdata.hpp>
#include <sway/render/procedurals/shape.hpp>

#include <memory>

namespace sway::render {
NS_BEGIN(procedurals)
NS_BEGIN(prims)

template <typename TVertexDataType>
class QuadrilateralStrip : public ShapeBase {
public:
  using VtxDataType_t = TVertexDataType;
  using IdxDataType_t = u32_t;

  static constexpr std::size_t MAX_QUAD_RESERVE_VERTICES{4};
  static constexpr std::size_t MAX_QUAD_RESERVE_ELEMENTS{6};

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  QuadrilateralStrip(const std::initializer_list<gapi::VertexSemantic> &semantics, const math::size2i_t &subdivs);

  DTOR_VIRTUAL_DEFAULT(QuadrilateralStrip);

  /** @} */
#pragma endregion

  auto getReserveVerts() const;

  auto getReserveElems() const;

  void initialVtxData();

  void initialElmData();

  void setPosDataAttrib(const math::rect4f_t &coords, f32_t zindex = 0.0F);

  void setColDataAttrib(const math::col4f_t &col);

  void setTexDataAttrib(const math::rect4f_t &tex);

  [[nodiscard]] auto data() const -> std::shared_ptr<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>>;

  MTHD_OVERRIDE(auto getVertexAttribs() const -> GeomVertexAttribSharedPtrMap_t);

  MTHD_OVERRIDE(void getVertices(void *dst, u32_t start, u32_t end));

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

NS_END()  // namespace prims
NS_END()  // namespace procedurals
}  // namespace sway::render

#include <sway/render/procedurals/prims/quadrilateralstrip.inl>

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_QUADRILATERALSTRIP_HPP
