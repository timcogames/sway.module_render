#ifndef SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_HPP
#define SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_HPP

#include <sway/math.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/geometryindexedvertexdata.hpp>
#include <sway/render/geometryvertexattribset.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/shape.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(procedurals)
NAMESPACE_BEGIN(prims)

template <typename TVertexDataType>
class Plane : public Shape {
public:
  Plane(const math::size2f_t &size, const math::size2i_t &subdivisions, const math::col4f_t &col = COL4F_WHITE)
      : data_(std::make_shared<GeometryIndexedVertexData<TVertexDataType>>(
            4 * subdivisions.getW() * subdivisions.getH())) {
    auto sizeHalf = size / 2.0F;

    GeometryVertexAttribSet attribs = {
        .pos = data_->template createVertexAttrib<math::vec3f_t>(gapi::VertexSemantic::POS),
        .col = data_->template createVertexAttrib<math::vec4f_t>(gapi::VertexSemantic::COL),
        .tex = data_->template createVertexAttrib<math::vec2f_t>(gapi::VertexSemantic::TEXCOORD_0)};

    auto unitScale = 1.5F;
    auto tileWt = size.getW() * unitScale;
    auto tileHt = size.getH() * unitScale;

    u32_t tileCount = 0;

    for (auto y = 0; y < subdivisions.getH(); y++) {
      for (auto x = 0; x < subdivisions.getW(); x++) {
        // posAttrib->addVtxData({-sizeHalf.getW(), -sizeHalf.getH(), 0.0F});
        // posAttrib->addVtxData({+sizeHalf.getW(), -sizeHalf.getH(), 0.0F});
        // posAttrib->addVtxData({-sizeHalf.getW(), +sizeHalf.getH(), 0.0F});
        // posAttrib->addVtxData({+sizeHalf.getW(), +sizeHalf.getH(), 0.0F});

        attribs.pos->addVtxData({(0.0F + (f32_t)x) * tileWt, (0.0F + (f32_t)y) * tileHt, 0.0F});
        attribs.pos->addVtxData({(1.0F + (f32_t)x) * tileWt, (0.0F + (f32_t)y) * tileHt, 0.0F});
        attribs.pos->addVtxData({(0.0F + (f32_t)x) * tileWt, (1.0F + (f32_t)y) * tileHt, 0.0F});
        attribs.pos->addVtxData({(1.0F + (f32_t)x) * tileWt, (1.0F + (f32_t)y) * tileHt, 0.0F});

        attribs.col->addVtxData(col.toVec4());
        attribs.col->addVtxData(col.toVec4());
        attribs.col->addVtxData(col.toVec4());
        attribs.col->addVtxData(col.toVec4());

        attribs.tex->addVtxData(math::vec2f_t(1.0F, 1.0F));
        attribs.tex->addVtxData(math::vec2f_t(0.0F, 1.0F));
        attribs.tex->addVtxData(math::vec2f_t(1.0F, 0.0F));
        attribs.tex->addVtxData(math::vec2f_t(0.0F, 0.0F));

        // data_->addTriIndices(0, 2, 1);
        // data_->addTriIndices(1, 2, 3);
        data_->addTriIndices(0 + (tileCount * 4), 2 + (tileCount * 4), 1 + (tileCount * 4));
        data_->addTriIndices(1 + (tileCount * 4), 2 + (tileCount * 4), 3 + (tileCount * 4));

        tileCount++;
      }
    }
  }

  ~Plane() = default;

  [[nodiscard]] auto getGeometryData() const -> GeometryDataPtr<TVertexDataType> { return data_; }

  template <std::size_t TSize>
  void useVertexSemanticSet(std::array<sway::gapi::VertexSemantic, TSize> &arr) {
    data_->useVertexSemanticSet(arr);
  }

  // void useVertexSemanticSet(std::vector<sway::gapi::VertexSemantic> &semantics) {
  //   // stringstream strm;
  //   // std::copy(semantics.begin(), semantics.end(), std::ostream_iterator<std::string>(strm, "\n"));
  //   // data_->useVertexSemanticSet(strm);
  // }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttribs() const -> VertexAttribMap_t) {  // clang-format on
    return data_->getAttribs();
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertexAttrib(gapi::VertexSemantic semantic) const -> VertexAttribPtr_t) {  // clang-format on
    return data_->getAttrib(semantic);
  }

  // clang-format off
  MTHD_OVERRIDE(auto getGeometryInfo() const -> GeometryCreateInfo) {  // clang-format on
    GeometryCreateInfo info;

    info.topology = gapi::TopologyType::TRIANGLE_LIST;
    info.vb.desc.usage = gapi::BufferUsage::STATIC;
    info.vb.desc.byteStride = sizeof(TVertexDataType);
    info.vb.desc.capacity = data_->getVtxCount();
    info.vb.data = data_->getVtxRawdata();

    info.ib.desc.usage = gapi::BufferUsage::STATIC;
    info.ib.desc.byteStride = sizeof(u32_t);
    info.ib.desc.capacity = data_->getIdxCount();
    info.ib.data = data_->getIndices().data();

    return info;
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVertices() -> void *) {  // clang-format on
    return data_->getVtxRawdata();
  }

private:
  GeometryDataPtr<TVertexDataType> data_;
};

NAMESPACE_END(prims)
NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PROCEDURALS_PRIMS_PLANE_HPP
