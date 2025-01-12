#ifndef SWAY_RENDER_PRINS_PRIM_HPP
#define SWAY_RENDER_PRINS_PRIM_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/_typedefs.hpp>
#include <sway/render/geom/geomcreateinfo.hpp>
#include <sway/render/geom/geomvertexattrib.hpp>

#include <map>

namespace sway::render {
NS_BEGIN(procedurals)

class ShapeBase {
public:
  PURE_VIRTUAL(auto getVertexAttribs() const -> GeomVertexAttribSharedPtrMap_t);

  PURE_VIRTUAL(void getVertices(void *dst, u32_t start, u32_t end));

  PURE_VIRTUAL(auto isIndexed() -> bool);

  PURE_VIRTUAL(auto mustBeRemapped() -> bool);

  PURE_VIRTUAL(void setRemap(bool val));
};

NS_END()  // namespace procedurals
}  // namespace sway::render

#endif  // SWAY_RENDER_PRINS_PRIM_HPP
