#include <sway/render/experience/pass/pass.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

auto Pass::get(const PassDescriptor &desc) -> PassTypedefs::Ptr_t {
  //   return RenderModule::getInternalContext()->currPipeline->getPassCache()->getOrCreate(desc);
}

Pass::Pass(const PassDescriptor &desc)
    : dirty_(true) {}

void Pass::dispose() {}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
