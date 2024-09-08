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
  auto createAttrib(gapi::VertexSemantic semantic) -> GeomVertexAttribBase::SharedPtr_t;

  auto getAttrib(gapi::VertexSemantic semantic) -> GeomVertexAttribBase::SharedPtr_t {
    auto iter = attribs_.find(semantic);
    if (iter != attribs_.end()) {
      return iter->second;
    }

    return nullptr;
  }

  [[nodiscard]]
  auto getAttribs() const -> std::map<gapi::VertexSemantic, GeomVertexAttribBase::SharedPtr_t> {
    return attribs_;
  }

  template <class TVertexSemanticIter>
  void useSemanticSet(TVertexSemanticIter first, TVertexSemanticIter last) {
    for (auto semantic = first; semantic != last; ++semantic) {
      auto attrib = this->getAttrib(*semantic);
      if (!attrib) {
        return;
      }

      attrib->use();
    }
  }

  MTHD_OVERRIDE(void useSemanticSet(const std::initializer_list<gapi::VertexSemantic> &semantics)) {
    this->useSemanticSet(semantics.begin(), semantics.end());
  }

  MTHD_OVERRIDE(auto getVtxSize() const -> u32_t) { return numVerts_; }

  void getVertices(void *dst, u32_t offset, u32_t numVerts) {
    auto len = offset + numVerts;
    auto nextAttrib = 0;

    for (auto i = offset; i < len; ++i) {
      for (auto [_, attrib] : attribs_) {
        if (!attrib->enabled()) {
          break;
        }

        attrib->getData(dst, nextAttrib, i);

        auto attribDesc = attrib->getDescriptor();
        nextAttrib += attribDesc.numComponents;
      }
    }
  }

private:
  std::map<gapi::VertexSemantic, GeomVertexAttribBase::SharedPtr_t> attribs_;
  u32_t numVerts_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#include <sway/render/geom/geomvertexdata.inl>

#endif  // SWAY_RENDER_GEOMVERTEXDATA_HPP
