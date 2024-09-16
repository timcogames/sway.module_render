#include <sway/render/rendertarget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

void RenderTarget::setScissorViewport(gapi::ViewportPtr_t viewport) { viewport_ = viewport; }

void RenderTarget::activate() {
  viewport_->setClearColor(math::col4f_t(50.0F, 50.0F, 50.0F, 1.0F));
  // viewport_->clear(gapi::ClearFlag::COLOR | gapi::ClearFlag::DEPTH | gapi::ClearFlag::STENCIL);
  viewport_->clear(gapi::ClearFlag::NONE);
}

void RenderTarget::deactivate() {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
