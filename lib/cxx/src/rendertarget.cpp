#include <sway/render/rendertarget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

void RenderTarget::setScissorViewport(gapi::ViewportPtr_t viewport) { viewport_ = viewport; }

void RenderTarget::activate() {
  viewport_->setClearColor(math::col4f_t(100.0F, 100.0F, 100.0F, 1.0F));
  viewport_->clear(gapi::ClearFlag::COLOR | gapi::ClearFlag::DEPTH | gapi::ClearFlag::STENCIL);
}

void RenderTarget::deactivate() {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
