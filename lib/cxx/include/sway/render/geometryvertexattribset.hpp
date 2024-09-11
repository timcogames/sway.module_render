#ifndef SWAY_RENDER_GEOMETRYVERTEXATTRIBSET_HPP
#define SWAY_RENDER_GEOMETRYVERTEXATTRIBSET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/geom/geomvertexattrib.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct GeomVertexAttribSet {
  GeomVertexAttribBase::SharedPtr_t pos;
  GeomVertexAttribBase::SharedPtr_t col;
  GeomVertexAttribBase::SharedPtr_t tex;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMETRYVERTEXATTRIBSET_HPP
