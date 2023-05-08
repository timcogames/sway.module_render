#ifndef SWAY_RENDER_GEOMETRYCREATEINFO_HPP
#define SWAY_RENDER_GEOMETRYCREATEINFO_HPP

#include <sway/gapi/buffercreateinfo.hpp>
#include <sway/gapi/topologytypes.hpp>
#include <sway/namespacemacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct GeometryCreateInfo {
  gapi::TopologyType topology;
  gapi::BufferCreateInfo vb;
  gapi::BufferCreateInfo ib;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMETRYCREATEINFO_HPP
