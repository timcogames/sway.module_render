#ifndef SWAY_RENDER_GEOMETRYVERTEXDATA_HPP
#define SWAY_RENDER_GEOMETRYVERTEXDATA_HPP

#include <sway/core.hpp>
#include <sway/render/geometryvertexattrib.hpp>
#include <sway/render/prereqs.hpp>

#include <stdlib.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

using VertexAttribPtr_t = std::shared_ptr<gapi::VertexAttrib>;
using VertexAttribMap_t = std::map<gapi::VertexSemantic, VertexAttribPtr_t>;

template <typename TVertexDataType>
class GeometryVertexData {
public:
  GeometryVertexData(s32_t count)
      : vtxcount_(count) {}

  ~GeometryVertexData() = default;

  template <typename TAttribFormat>
  auto createVertexAttrib(gapi::VertexSemantic semantic, s32_t reserve)
      -> std::shared_ptr<GeometryVertexAttrib<TAttribFormat>> {
    auto attrib = std::make_shared<GeometryVertexAttrib<TAttribFormat>>(semantic, reserve);
    attribs_[semantic] = attrib;
    return attrib;
  }

  template <std::size_t TSize>
  void useVertexSemanticSet(std::array<sway::gapi::VertexSemantic, TSize> &semantics) {
    for (auto semantic : semantics) {
      auto attrib = getAttrib(semantic);
      if (!attrib) {
        return;
      }

      attrib->use();
    }
  }

  auto getAttrib(gapi::VertexSemantic semantic) -> VertexAttribPtr_t {
    auto iter = attribs_.find(semantic);
    if (iter != attribs_.end()) {
      return iter->second;
    }

    return nullptr;
  }

  [[nodiscard]]
  auto getAttribs() const -> VertexAttribMap_t {
    return attribs_;
  }

  auto getVtxRawdata() -> void * {
    s32_t offset = 0;
    void *vtxdata = (void *)calloc(vtxcount_, sizeof(TVertexDataType));

    for (auto i = 0; i < vtxcount_; ++i) {
      for (auto [_, attrib] : attribs_) {
        if (attrib->isEnabled()) {
          attrib->importRawdata(vtxdata, offset, i);
          offset += attrib->getDescriptor().numComponents;
        }
      }
    }

    return vtxdata;
  }

  [[nodiscard]]
  auto getVtxCount() const -> u32_t {
    return vtxcount_;
  }

private:
  VertexAttribMap_t attribs_;
  s32_t vtxcount_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMETRYVERTEXDATA_HPP
