#include <sway/render/renderqueuepass.hpp>
#include <sway/render/rendersubqueue.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

RenderQueuePass::RenderQueuePass(const std::string &name)
    : RenderPass(name) {}

void RenderQueuePass::apply(gapi::Framebuffer::Ptr_t framebuf) {}

void RenderQueuePass::execute() {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
