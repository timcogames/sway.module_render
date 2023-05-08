#ifndef SWAY_RENDER_RENDERPASS_HPP
#define SWAY_RENDER_RENDERPASS_HPP

#include <sway/namespacemacros.hpp>
#include <sway/render/rendertarget.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderPass {
public:
  RenderPass();

  ~RenderPass() = default;

  void setRenderTarget(std::shared_ptr<RenderTarget> target) { target_ = target; }

  auto getRenderTarget() -> std::shared_ptr<RenderTarget> { return target_; }

private:
  std::shared_ptr<RenderTarget> target_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERPASS_HPP
