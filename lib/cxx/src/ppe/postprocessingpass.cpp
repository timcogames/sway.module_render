#include <sway/render/ppe/postprocessingpass.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

PostProcessingPass::PostProcessingPass(const std::string &name)
    : RenderPass(name)
    , target_(nullptr)
    , state_(nullptr) {}

void PostProcessingPass::apply(gapi::Framebuffer::Ptr_t framebuf) {}

void PostProcessingPass::execute() {}

NS_END()  // namespace render
NS_END()  // namespace sway
