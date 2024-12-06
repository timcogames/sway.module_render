#include <sway/core/runtime/log.hpp>
#include <sway/render/experience/pass/specs/graphicspass.hpp>

#define TRACE_CTORS_DTOR 0
#define TRACE_PARAMETERS 0

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

GraphicsPass::GraphicsPass(const PassDescriptor &desc)
    : Pass(desc) {
#if TRACE_CTORS_DTOR
  core::runtime::LOG("GraphicsPass::Ctor");
#endif
}

GraphicsPass::~GraphicsPass() {
#if TRACE_CTORS_DTOR
  core::runtime::LOG("GraphicsPass::Dtor");
#endif
}

void GraphicsPass::execute(OperationContext *ctx) { queue_->process(ctx); }

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
