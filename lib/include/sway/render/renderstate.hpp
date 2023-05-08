#ifndef SWAY_RENDER_RENDERSTATE_HPP
#define SWAY_RENDER_RENDERSTATE_HPP

#include <sway/namespacemacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderState {
public:
  RenderState() = default;

  ~RenderState() = default;

  void restore();
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERSTATE_HPP
