#ifndef SWAY_RENDER_PPE_POSTPROCESSINGPASS_HPP
#define SWAY_RENDER_PPE_POSTPROCESSINGPASS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/ppe/screenquad.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderstate.hpp>
#include <sway/render/rendertarget.hpp>
#include <sway/render/temp/pipeline/stage/pass/pass.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(render)

// class PostProcessingPass : public IRenderPass {
//   DECLARE_PTR_ALIASES(PostProcessingPass)

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

class PostProcessingPass : public Pass {
  DECLARE_PTR_ALIASES(PostProcessingPass)

public:
#pragma region "Ctors/Dtor"

  PostProcessingPass(const std::string &name, ScreenQuad::SharedPtr_t quad);

  DTOR_VIRTUAL_DEFAULT(PostProcessingPass);

#pragma endregion

#pragma region "Override Pass methods"

  MTHD_OVERRIDE(void setup()) {}

  MTHD_OVERRIDE(void dispose()) {}

  MTHD_OVERRIDE(void apply(gapi::FrameBuffer::Ptr_t framebuf));

  MTHD_OVERRIDE(void execute());

#pragma endregion

  void setRenderTarget(RenderTarget::SharedPtr_t target) { target_ = target; }

  auto getRenderTarget() -> RenderTarget::SharedPtr_t { return target_; }

  void setRenderState(RenderState::SharedPtr_t state) { state_ = state; }

  auto getRenderState() -> RenderState::SharedPtr_t { return state_; }

  auto isEnabled() -> bool { return enabled_; }

  void setEnabled(bool val) { enabled_ = val; }

private:
  RenderTarget::SharedPtr_t target_;
  RenderState::SharedPtr_t state_;
  ScreenQuad::SharedPtr_t quad_;
  bool enabled_;

  math::mat4f_t vp_;
  math::mat4f_t tfrm_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PPE_POSTPROCESSINGPASS_HPP
