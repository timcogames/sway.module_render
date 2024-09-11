#ifndef SWAY_RENDER_PRINS_PRIM_HPP
#define SWAY_RENDER_PRINS_PRIM_HPP

#include <sway/render/geom/geomvertexattrib.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/prereqs.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(procedurals)

class ShapeBase {
public:
  PURE_VIRTUAL(auto getVertexAttribs() const->std::map<gapi::VertexSemantic, GeomVertexAttribBase::SharedPtr_t>);

  PURE_VIRTUAL(void getVertices(void *dst, u32_t start, u32_t end));

  PURE_VIRTUAL(auto isIndexed() -> bool);

  PURE_VIRTUAL(auto mustBeRemapped() -> bool);

  PURE_VIRTUAL(void setRemap(bool val));
};

NAMESPACE_END(procedurals)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PRINS_PRIM_HPP
