#include <sway/render/ppe/postprocessing.hpp>
#include <sway/render/renderstages.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

PostProcessing::PostProcessing(gapi::ViewportPtr_t viewport) {
  viewport_ = viewport;
  state_ = std::make_shared<RenderState>();
}

// void PostProcessing::addPass(u32_t idx, RenderTarget::SharedPtr_t target) {
//   passes_[idx] = std::make_shared<RenderPass>();
//   target->setScissorViewport(viewport_);
//   if (idx == core::detail::toBase(RenderStage::IDX_COLOR)) {
//     target->attachColorBufferObject();
//   }

//   passes_[idx]->setRenderTarget(target);

//   passes_[idx]->setRenderState(state_);
// }

void PostProcessing::add(RenderPass::SharedPtr_t pass, i32_t idx) {
  if (idx < 0) {
    passes_.push_back(pass);
  } else {
    passes_.insert(passes_.begin() + idx, pass);
  }
}

void PostProcessing::apply(gapi::Framebuffer::Ptr_t framebuf) {
  for (auto &pass : passes_) {
    pass->apply(framebuf);
  }
}

auto PostProcessing::getPass(u32_t idx) -> RenderPass::SharedPtr_t { return passes_[idx]; }

void PostProcessing::preRender() {}

void PostProcessing::postRender() {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
