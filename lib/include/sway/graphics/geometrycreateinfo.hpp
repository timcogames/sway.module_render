#ifndef SWAY_GRAPHICS_GEOMETRYCREATEINFO_HPP
#define SWAY_GRAPHICS_GEOMETRYCREATEINFO_HPP

#include <sway/gapi/buffercreateinfo.hpp>
#include <sway/gapi/topologytypes.hpp>
#include <sway/namespacemacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

struct GeometryCreateInfo {
  gapi::BufferCreateInfo vb;
  gapi::BufferCreateInfo ib;
  gapi::TopologyType topology;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_GEOMETRYCREATEINFO_HPP
