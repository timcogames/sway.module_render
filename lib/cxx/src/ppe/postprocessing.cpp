#include <sway/render/ppe/postprocessing.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

PostProcessing::PostProcessing(gapi::ViewportPtr_t viewport) {
  target_ = std::make_shared<RenderTarget>();
  target_->setScissorViewport(viewport);
  state_ = std::make_shared<RenderState>();
}

void PostProcessing::addPass(u32_t idx) {
  passes_[idx] = std::make_shared<RenderPass>();
  passes_[idx]->setRenderTarget(target_);
  passes_[idx]->setRenderState(state_);
}

void PostProcessing::preRender() {}

void PostProcessing::postRender() {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
