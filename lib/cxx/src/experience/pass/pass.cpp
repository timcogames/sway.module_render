#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/utility/cache.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

auto Pass::get(const PipelineDescriptor &pipeDesc, const PassDescriptor &passDesc) -> PassTypedefs::Ptr_t {
  auto ctx = RenderModule::getInternalContext();
  return ctx->pipeCache->getOrCreate<PipelineDescriptor, Pipeline>(pipeDesc)
      ->passes()
      ->getOrCreate<PassDescriptor, Pass>(passDesc);
}

Pass::Pass(const PassDescriptor &desc)
    : dirty_(true) {}

void Pass::dispose() {}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
