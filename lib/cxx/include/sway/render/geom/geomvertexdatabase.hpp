#ifndef SWAY_RENDER_GEOMVERTEXDATABASE_HPP
#define SWAY_RENDER_GEOMVERTEXDATABASE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <initializer_list>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class GeomVertexDataBase {
public:
  PURE_VIRTUAL(auto getVtxSize() const -> u32_t);

  PURE_VIRTUAL(void useSemanticSet(const std::initializer_list<gapi::VertexSemantic> &semantics));
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMVERTEXDATABASE_HPP
