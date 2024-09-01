#ifndef SWAY_RENDER_PIPELINE_BLENDDESCRIPTOR_HPP
#define SWAY_RENDER_PIPELINE_BLENDDESCRIPTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(pipeline)

struct BlendDescriptor {
  bool enabled;
  gapi::BlendFn src;
  gapi::BlendFn dst;
  bool mask;
};

NAMESPACE_END(pipeline)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PIPELINE_BLENDDESCRIPTOR_HPP
