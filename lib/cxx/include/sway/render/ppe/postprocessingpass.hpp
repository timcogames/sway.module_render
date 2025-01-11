#ifndef SWAY_RENDER_PPE_POSTPROCESSINGPASS_HPP
#define SWAY_RENDER_PPE_POSTPROCESSINGPASS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/ppe/screenquad.hpp>
#include <sway/render/renderstate.hpp>
#include <sway/render/rendertarget.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(render)

// class PostProcessingPass : public IRenderPass {
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

class PostProcessingPass {
public:
#pragma region "Ctors/Dtor"

  PostProcessingPass(const std::string &name, typedefs::ScreenQuadSharedPtr_t quad);

  DTOR_VIRTUAL_DEFAULT(PostProcessingPass);

#pragma endregion

  void setup() {}

  void dispose() {}

  void apply(gapi::typedefs::FrameBufferPtr_t framebuf);

  void execute();

  void setRenderTarget(typedefs::RenderTargetSharedPtr_t target) { target_ = target; }

  auto getRenderTarget() -> typedefs::RenderTargetSharedPtr_t { return target_; }

  void setRenderState(typedefs::RenderStateSharedPtr_t state) { state_ = state; }

  auto getRenderState() -> typedefs::RenderStateSharedPtr_t { return state_; }

  auto isEnabled() -> bool { return enabled_; }

  void setEnabled(bool val) { enabled_ = val; }

private:
  typedefs::RenderTargetSharedPtr_t target_;
  typedefs::RenderStateSharedPtr_t state_;
  typedefs::ScreenQuadSharedPtr_t quad_;
  bool enabled_;

  math::mat4f_t vp_;
  math::mat4f_t tfrm_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PPE_POSTPROCESSINGPASS_HPP
