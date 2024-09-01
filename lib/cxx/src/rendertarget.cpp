#include <sway/render/rendertarget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

void RenderTarget::setScissorViewport(gapi::ViewportPtr_t viewport) { viewport_ = viewport; }

void RenderTarget::activate() { viewport_->clear(); }

void RenderTarget::deactivate() {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
