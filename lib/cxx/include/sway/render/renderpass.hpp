#ifndef SWAY_RENDER_RENDERPASS_HPP
#define SWAY_RENDER_RENDERPASS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderstate.hpp>
#include <sway/render/rendertarget.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

// enum class RenderPassType : u32_t { DEPTH, COLOR, REFRACT, BLENDED, SENTINEL };
// enum class RenderPassAction { KEEP = 0, CLEAR = 1, DONT_CARE = 2 };

// struct RenderPassInfo {
//   RenderPassAction color;
//   RenderPassAction depth;
//   RenderPassAction stencil;
//   u32_t clearColor;
//   u32_t clearDepth;
//   u32_t clearStencil;
// };

class RenderPass {
  DECLARE_CLASS_POINTER_ALIASES(RenderPass)

public:
#pragma region "Ctors/Dtor"

  RenderPass();

  ~RenderPass() = default;

#pragma endregion

  void setRenderTarget(RenderTarget::SharedPtr_t target) { target_ = target; }

  auto getRenderTarget() -> RenderTarget::SharedPtr_t { return target_; }

  void setRenderState(RenderState::SharedPtr_t state) { state_ = state; }

  auto getRenderState() -> RenderState::SharedPtr_t { return state_; }

private:
  RenderTarget::SharedPtr_t target_;
  RenderState::SharedPtr_t state_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERPASS_HPP
