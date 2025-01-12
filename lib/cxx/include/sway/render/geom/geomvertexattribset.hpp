#ifndef SWAY_RENDER_GEOMVERTEXATTRIBSET_HPP
#define SWAY_RENDER_GEOMVERTEXATTRIBSET_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/_typedefs.hpp>
#include <sway/render/geom/geomvertexattrib.hpp>

#include <memory>

namespace sway::render {

struct GeomVertexAttribSet {
  GeomVertexAttribBaseSharedPtr_t pos;
  GeomVertexAttribBaseSharedPtr_t col;
  GeomVertexAttribBaseSharedPtr_t tex;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_GEOMVERTEXATTRIBSET_HPP
