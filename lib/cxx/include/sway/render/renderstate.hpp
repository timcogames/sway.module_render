#ifndef SWAY_RENDER_RENDERSTATE_HPP
#define SWAY_RENDER_RENDERSTATE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderState {
  DECLARE_CLASS_POINTER_ALIASES(RenderState)

public:
#pragma region "Ctors/Dtor"

  RenderState();

  ~RenderState() = default;

#pragma endregion

  void restore();

  auto getContext() -> gapi::StateContextPtr_t { return state_; }

private:
  gapi::StateContextPtr_t state_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERSTATE_HPP
