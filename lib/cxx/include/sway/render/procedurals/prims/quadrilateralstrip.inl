#include <sway/render/procedurals/prims/quadrilateralstrip.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(procedurals)
NS_BEGIN(prims)

template <typename TVertexDataType>
QuadrilateralStrip<TVertexDataType>::QuadrilateralStrip(
    const std::initializer_list<gapi::VertexSemantic> &semantics, const math::size2i_t &subdivs)
    : numChunks_(subdivs.getW() + 1, subdivs.getH() + 1)
    , area_(subdivs.area())
    , remapping_(false) {
  initialVtxData();
  initialElmData();

  data_->useSemanticSet(semantics);
}

template <typename TVertexDataType>
auto QuadrilateralStrip<TVertexDataType>::getReserveVerts() const {
  return MAX_QUAD_RESERVE_VERTICES * (area_ > 1 ? 4 : 1);
}

template <typename TVertexDataType>
auto QuadrilateralStrip<TVertexDataType>::getReserveElems() const {
  return MAX_QUAD_RESERVE_ELEMENTS * (area_);
}

template <typename TVertexDataType>
void QuadrilateralStrip<TVertexDataType>::initialVtxData() {
  data_ = std::make_shared<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>>(getReserveVerts(), getReserveElems());

  // clang-format off
  dataAttribs_ = (struct GeomVertexAttribSet) {
    .pos = data_->template createAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
    .col = data_->template createAttrib<math::vec4f_t>(gapi::VertexSemantic::COL),
    .tex = data_->template createAttrib<math::vec2f_t>(gapi::VertexSemantic::TEXCOORD_0)
  };
  // clang-format on
}

template <typename TVertexDataType>
void QuadrilateralStrip<TVertexDataType>::initialElmData() {
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

template <typename TVertexDataType>
void QuadrilateralStrip<TVertexDataType>::setPosDataAttrib(const math::rect4f_t &coords, f32_t zindex) {
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

    auto data = math::vec3f_t(xpos, ypos, zindex);
    dataAttribs_.pos->setData(offset, data.asDataPtr());
    offset += 1;
  }
}

template <typename TVertexDataType>
void QuadrilateralStrip<TVertexDataType>::setColDataAttrib(const math::col4f_t &col) {
  auto offset = 0;
  for (auto y = 0; y < numChunks_.getY(); y++) {
    for (auto x = 0; x < numChunks_.getX(); x++) {
      dataAttribs_.col->setData(offset, col.asVec4().asDataPtr());
      offset += 1;
    }
  }
}

template <typename TVertexDataType>
void QuadrilateralStrip<TVertexDataType>::setTexDataAttrib(const math::rect4f_t &tex) {
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

template <typename TVertexDataType>
auto QuadrilateralStrip<TVertexDataType>::data() const
    -> std::shared_ptr<GeomIndexedVertexData<VtxDataType_t, IdxDataType_t>> {
  return data_;
}

template <typename TVertexDataType>
auto QuadrilateralStrip<TVertexDataType>::getVertexAttribs() const -> GeomVertexAttribSharedPtrMap_t {
  return data_->getAttribs();
}

template <typename TVertexDataType>
void QuadrilateralStrip<TVertexDataType>::getVertices(void *dst, u32_t start, u32_t end) {
  data_->getVertices(dst, start, end);
}

NS_END()  // namespace prims
NS_END()  // namespace procedurals
NS_END()  // namespace render
NS_END()  // namespace sway
