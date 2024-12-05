#include <sway/render/experience/pass/specs/graphicspass.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

GraphicsPass::GraphicsPass(const PassDescriptor &desc)
    : Pass(desc) {}

void GraphicsPass::execute() { queue_->process(); }

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
