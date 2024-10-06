#ifndef SWAY_RENDER_PPE_POSTPROCESSINGPASS_HPP
#define SWAY_RENDER_PPE_POSTPROCESSINGPASS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderpass.hpp>
#include <sway/render/renderstate.hpp>
#include <sway/render/rendertarget.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

// class PostProcessingPass : public IRenderPass {
//   DECLARE_CLASS_POINTER_ALIASES(PostProcessingPass)

// public:
//   PostProcessingPass(const std::string &name, const core::misc::Dictionary &glob)
//       : IRenderPass(name)
//       , screenWdt_((f32_t)glob.getIntegerOrDefault("screen_wdt", 800))
//       , screenHgt_((f32_t)glob.getIntegerOrDefault("screen_hgt", 600)) {}

//   virtual ~PostProcessingPass() = default;

//   // auto isColorBufferOutput() -> bool { return true; }

//   // auto isDepthBufferOutput() -> bool { return true; }

//   MTHD_OVERRIDE(void apply(FrameBuffer &frameBuffer, const RenderMetaData &metadata)) {}

// private:
//   f32_t screenWdt_;
//   f32_t screenHgt_;
// };

class PostProcessingEffect {};

class PostProcessingPass : public RenderPass {
  DECLARE_CLASS_POINTER_ALIASES(PostProcessingPass)

public:
#pragma region "Ctors/Dtor"

  PostProcessingPass(const std::string &name);

  virtual ~PostProcessingPass() = default;

#pragma endregion

#pragma region "Override RenderPass methods"

  MTHD_OVERRIDE(void apply(gapi::Framebuffer::Ptr_t framebuf));

  MTHD_OVERRIDE(void execute());

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

#endif  // SWAY_RENDER_PPE_POSTPROCESSINGPASS_HPP
