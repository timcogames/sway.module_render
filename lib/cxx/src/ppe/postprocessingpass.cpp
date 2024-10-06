#include <sway/render/ppe/postprocessingpass.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

PostProcessingPass::PostProcessingPass(const std::string &name)
    : RenderPass(name)
    , target_(nullptr)
    , state_(nullptr) {}

void PostProcessingPass::apply(gapi::Framebuffer::Ptr_t framebuf) {}

void PostProcessingPass::execute() {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
