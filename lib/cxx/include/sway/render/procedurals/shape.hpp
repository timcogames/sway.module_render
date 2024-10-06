#ifndef SWAY_RENDER_PRINS_PRIM_HPP
#define SWAY_RENDER_PRINS_PRIM_HPP

#include <sway/render/geom/geomvertexattrib.hpp>
#include <sway/render/geometrycreateinfo.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/typedefs.hpp>

#include <map>

NS_BEGIN_SWAY()
NS_BEGIN(render)
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
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PRINS_PRIM_HPP
