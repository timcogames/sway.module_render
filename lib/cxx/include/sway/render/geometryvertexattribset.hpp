#ifndef SWAY_RENDER_GEOMETRYVERTEXATTRIBSET_HPP
#define SWAY_RENDER_GEOMETRYVERTEXATTRIBSET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/geom/geomvertexattrib.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(render)

struct GeomVertexAttribSet {
  GeomVertexAttribBase::SharedPtr_t pos;
  GeomVertexAttribBase::SharedPtr_t col;
  GeomVertexAttribBase::SharedPtr_t tex;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_GEOMETRYVERTEXATTRIBSET_HPP
