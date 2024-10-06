#include <sway/render/renderqueuepass.hpp>
#include <sway/render/rendersubqueue.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

RenderQueuePass::RenderQueuePass(const std::string &name)
    : RenderPass(name) {}

void RenderQueuePass::apply(gapi::Framebuffer::Ptr_t framebuf) {}

void RenderQueuePass::execute() {}

NS_END()  // namespace render
NS_END()  // namespace sway
