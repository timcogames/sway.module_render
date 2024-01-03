#include <sway/render/rendertarget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

void RenderTarget::setScissorViewport(std::shared_ptr<gapi::Viewport> viewport) {
  viewport_ = viewport;
  // viewport_->set(0, 0, 100, 100);
}

void RenderTarget::activate() {
  // viewport_->clear();
}

void RenderTarget::deactivate() {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
