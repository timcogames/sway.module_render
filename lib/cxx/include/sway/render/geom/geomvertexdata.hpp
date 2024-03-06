#ifndef SWAY_RENDER_GEOMVERTEXDATA_HPP
#define SWAY_RENDER_GEOMVERTEXDATA_HPP

#include <sway/core.hpp>
#include <sway/render/geom/geomvertexattrib.hpp>
#include <sway/render/geom/geomvertexdatabase.hpp>
#include <sway/render/prereqs.hpp>

#include <stdlib.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TVertexDataType>
class GeomVertexData : public GeomVertexDataBase {
public:
  GeomVertexData(u32_t numVerts)
      : numVerts_(numVerts) {}

  virtual ~GeomVertexData() = default;

  template <typename TAttribFormat>
  auto createAttrib(gapi::VertexSemantic semantic) -> std::shared_ptr<GeomVertexAttribBase>;

  auto getAttrib(gapi::VertexSemantic semantic) -> std::shared_ptr<GeomVertexAttribBase> {
    auto iter = attribs_.find(semantic);
    if (iter != attribs_.end()) {
      return iter->second;
    }

    return nullptr;
  }

  [[nodiscard]]
  auto getAttribs() const -> std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> {
    return attribs_;
  }

  MTHD_OVERRIDE(void useSemanticSet(const std::initializer_list<gapi::VertexSemantic> &semantics)) {
    for (auto semantic : semantics) {
      auto attrib = this->getAttrib(semantic);
      if (!attrib) {
        return;
      }

      attrib->use();
    }
  }

  // clang-format off
  MTHD_OVERRIDE(auto getVtxSize() const -> u32_t) {  // clang-format on
    return numVerts_;
  }

  auto getVertices() -> void * {
    auto offset = 0;
    auto *vertices = calloc(numVerts_, sizeof(TVertexDataType));

    for (auto i = 0; i < numVerts_; ++i) {
      for (auto [_, attrib] : attribs_) {
        if (!attrib->enabled()) {
          break;
        }

        attrib->getData(vertices, offset, i);

        auto attribDesc = attrib->getDescriptor();
        offset += attribDesc.numComponents;
      }
    }

    return vertices;
  }

private:
  std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs_;
  u32_t numVerts_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#include <sway/render/geom/geomvertexdata.inl>

#endif  // SWAY_RENDER_GEOMVERTEXDATA_HPP
