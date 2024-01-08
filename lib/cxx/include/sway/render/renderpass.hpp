#ifndef SWAY_RENDER_RENDERPASS_HPP
#define SWAY_RENDER_RENDERPASS_HPP

#include <sway/gapi.hpp>
#include <sway/namespacemacros.hpp>
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
public:
  RenderPass();

  ~RenderPass() = default;

  void setRenderTarget(std::shared_ptr<RenderTarget> target) { target_ = target; }

  auto getRenderTarget() -> std::shared_ptr<RenderTarget> { return target_; }

  void setRenderState(std::shared_ptr<RenderState> state) { state_ = state; }

  auto getRenderState() -> std::shared_ptr<RenderState> { return state_; }

private:
  std::shared_ptr<RenderTarget> target_;
  std::shared_ptr<RenderState> state_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERPASS_HPP
