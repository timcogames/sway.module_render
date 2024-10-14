#ifndef SWAY_RENDER_RENDERSTATE_HPP
#define SWAY_RENDER_RENDERSTATE_HPP

#include <sway/render/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class RenderState {
  DECLARE_PTR_ALIASES(RenderState)

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

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERSTATE_HPP
