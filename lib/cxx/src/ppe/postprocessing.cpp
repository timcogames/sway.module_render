#include <sway/render/ppe/postprocessing.hpp>

namespace sway::render {

PostProcessing::PostProcessing(gapi::typedefs::ViewportPtr_t viewport) {
  viewport_ = viewport;
  state_ = std::make_shared<RenderState>();
}

// void PostProcessing::addPass(u32_t idx, RenderTargetSharedPtr_t target) {
//   passes_[idx] = std::make_shared<GraphicsPass>();
//   target->setScissorViewport(viewport_);
//   if (idx == core::toBase(RenderStage::IDX_COLOR)) {
//     target->attachColorBufferObject();
//   }

//   passes_[idx]->setRenderTarget(target);

//   passes_[idx]->setRenderState(state_);
// }

void PostProcessing::add(std::shared_ptr<PostProcessingPass> pass, i32_t idx) {
  if (idx < 0) {
    passes_.push_back(pass);
  } else {
    passes_.insert(passes_.begin() + idx, pass);
  }
}

void PostProcessing::apply(gapi::typedefs::FrameBufferPtr_t framebuf) {
  for (auto &pass : passes_) {
    pass->apply(framebuf);
  }
}

auto PostProcessing::getPass(u32_t idx) -> std::shared_ptr<PostProcessingPass> { return passes_[idx]; }

void PostProcessing::preRender() {}

void PostProcessing::postRender() {
  for (auto &pass : passes_) {
    pass->execute();
  }
}

}  // namespace sway::render
