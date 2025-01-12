#ifndef SWAY_RENDER_GEOMVERTEXDATABASE_HPP
#define SWAY_RENDER_GEOMVERTEXDATABASE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <initializer_list>

namespace sway::render {

class GeomVertexDataBase {
public:
  PURE_VIRTUAL(auto getVtxSize() const -> u32_t);

  PURE_VIRTUAL(void useSemanticSet(const std::initializer_list<gapi::VertexSemantic> &semantics));
};

}  // namespace sway::render

#endif  // SWAY_RENDER_GEOMVERTEXDATABASE_HPP
