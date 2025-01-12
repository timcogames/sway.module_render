// #include <sway/core/runtime/log.hpp>
#include <sway/render/experience/pass/specs/graphicspass.hpp>

#define TRACE_CTORS_DTOR 0
#define TRACE_PARAMETERS 0

namespace sway::render {
NS_BEGIN(experience)

GraphicsPass::GraphicsPass(const PassDescriptor &desc)
    : Pass(desc) {
#if TRACE_CTORS_DTOR
  // core::runtime::LOG("GraphicsPass::Ctor");
#endif
}

GraphicsPass::~GraphicsPass() {
#if TRACE_CTORS_DTOR
  // core::runtime::LOG("GraphicsPass::Dtor");
#endif
}

void GraphicsPass::execute(DeviceContextTypedefs::Ptr_t context) { queue_->process(context); }

NS_END()  // namespace experience
}  // namespace sway::render
