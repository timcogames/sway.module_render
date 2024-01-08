#ifndef SWAY_RENDER_RENDERSTATE_HPP
#define SWAY_RENDER_RENDERSTATE_HPP

#include <sway/gapi.hpp>
#include <sway/namespacemacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderState {
public:
  RenderState();

  ~RenderState() = default;

  void restore();

  auto getContext() -> std::shared_ptr<gapi::StateContext> { return state_; }

private:
  std::shared_ptr<gapi::StateContext> state_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERSTATE_HPP