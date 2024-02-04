#ifndef SWAY_RENDER_SPRITEBATCH_HPP
#define SWAY_RENDER_SPRITEBATCH_HPP

// #include <sway/cmpt/component.hpp>
#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/guides/axis.hpp>
#include <sway/render/procedurals/prims/plane.hpp>
#include <sway/render/rendercomponent.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

#define MAX_BATCH_QUADS 10000
#define MAX_BATCH_VERTICES 40000
#define MAX_BATCH_ELEMENTS 60000

#define QUAD_NUM_RESERVE_VERTICES 4

template <typename TVertexDataType>
class PlaneArray : public procedurals::Shape {
public:
  PlaneArray()
      : data_(std::make_shared<GeometryIndexedVertexData<TVertexDataType>>(MAX_BATCH_VERTICES)) {
    attribs_ = {
        .pos = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::POS, QUAD_NUM_RESERVE_VERTICES),
        .col = data_->template createVertexAttrib<math::vec4f_t>(gapi::VertexSemantic::COL, QUAD_NUM_RESERVE_VERTICES),
        .tex = data_->template createVertexAttrib<math::vec2f_t>(
            gapi::VertexSemantic::TEXCOORD_0, QUAD_NUM_RESERVE_VERTICES)};

    for (auto i = 0, offset = 0; i < MAX_BATCH_ELEMENTS; i += 6, offset += 4) {
      data_->addTriIndices(0 + offset, 1 + offset, 2 + offset);
      data_->addTriIndices(2 + offset, 3 + offset, 0 + offset);
    }
  }

  virtual ~PlaneArray() = default;

  void updateVertices(const math::point2f_t &pos, const math::size2f_t &size, const math::rect4f_t &tex) {
    // attribs_.pos->clear();
    attribs_.pos->addVtxData({pos.getX() + size.getW(), pos.getY(), 0.0F});
    attribs_.pos->addVtxData({pos.getX() + size.getW(), pos.getY() + size.getH(), 0.0F});
    attribs_.pos->addVtxData({pos.getX(), pos.getY() + size.getH(), 0.0F});
    attribs_.pos->addVtxData({pos.getX(), pos.getY(), 0.0F});

    // attribs_.col->clear();
    attribs_.col->addVtxData(COL4F_WHITE.toVec4());
    attribs_.col->addVtxData(COL4F_WHITE.toVec4());
    attribs_.col->addVtxData(COL4F_WHITE.toVec4());
    attribs_.col->addVtxData(COL4F_WHITE.toVec4());

    // attribs_.tex->clear();
    attribs_.tex->addVtxData(math::vec2f_t(tex.getL(), tex.getB()));
    attribs_.tex->addVtxData(math::vec2f_t(tex.getL(), tex.getT()));
    attribs_.tex->addVtxData(math::vec2f_t(tex.getR(), tex.getT()));
    attribs_.tex->addVtxData(math::vec2f_t(tex.getR(), tex.getB()));
  }

  [[nodiscard]]
  auto getGeometryData() -> GeometryDataPtr<TVertexDataType> {
    return data_;
  }

  template <std::size_t TSize>
  void useVertexSemanticSet(std::array<sway::gapi::VertexSemantic, TSize> &arr) {
    data_->useVertexSemanticSet(arr);
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttribs() const -> VertexAttribMap_t) {  // clang-format on
    return data_->getAttribs();
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttrib(gapi::VertexSemantic semantic) const -> VertexAttribPtr_t) {  // clang-format on
    return data_->getAttrib(semantic);
  }

  // clang-format off
  MTHD_OVERRIDE(auto getGeometryInfo() -> GeometryCreateInfo) {  // clang-format on
    GeometryCreateInfo info;

    info.topology = gapi::TopologyType::TRIANGLE_LIST;
    info.vb.desc.usage = gapi::BufferUsage::DYNAMIC;
    info.vb.desc.byteStride = sizeof(TVertexDataType);
    info.vb.desc.capacity = MAX_BATCH_VERTICES;
    info.vb.data = nullptr;

    info.ib.desc.usage = gapi::BufferUsage::STATIC;
    info.ib.desc.byteStride = sizeof(u32_t);
    info.ib.desc.capacity = MAX_BATCH_ELEMENTS;
    info.ib.data = data_->getIndices().data();

    return info;
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertices() -> void *) {  // clang-format on
    return data_->getVtxRawdata();
  }

public:
  GeometryVertexAttribSet attribs_;
  GeometryDataPtr<TVertexDataType> data_;
};

class SpriteBatch : public RenderComponent {
public:
  DECLARE_CLASS_METADATA(SpriteBatch, RenderComponent)

  SpriteBatch() = default;

  ~SpriteBatch() = default;

  void initialize(std::shared_ptr<RenderSubsystem> subsystem, std::shared_ptr<RenderSubqueue> subqueue,
      std::shared_ptr<Material> material, const math::size2f_t &size);

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime));

  [[nodiscard]]
  auto getMaterial() const -> std::shared_ptr<Material> {
    return material_;
  }

private:
  RenderSubqueueRef_t subqueue_;

  std::shared_ptr<Material> material_;
  std::shared_ptr<PlaneArray<math::VertexTexCoordEx>> geomShape_;
  std::shared_ptr<Geometry> geom_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_SPRITEBATCH_HPP
