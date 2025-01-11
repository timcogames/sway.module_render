#ifndef SWAY_RENDER_GEOMVERTEXATTRIBSET_HPP
#define SWAY_RENDER_GEOMVERTEXATTRIBSET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/geom/geomvertexattrib.hpp>
#include <sway/render/typedefs.hpp>

#include <memory>

namespace sway::render {

struct GeomVertexAttribSet {
  typedefs::GeomVertexAttribBaseSharedPtr_t pos;
  typedefs::GeomVertexAttribBaseSharedPtr_t col;
  typedefs::GeomVertexAttribBaseSharedPtr_t tex;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_GEOMVERTEXATTRIBSET_HPP
