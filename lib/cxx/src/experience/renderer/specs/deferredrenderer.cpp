
#include <sway/render/experience/pass/specs/graphicspass.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/renderer/specs/deferredrenderer.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/technique/techniquemanager.hpp>

namespace sway::render {
NS_BEGIN(experience)

void DeferredRenderer::registerTechnique(CommandQueueTypedefs::UniquePtr_t &queue) {
  // clang-format off
  RenderModule::getInternalContext()->techniqueMngr->registerTechnique("deferred", 
    [&](Technique &tech, const TechniqueMetadata &meta) {
      // Empty
    });
  // clang-format on
}

DeferredRenderer::DeferredRenderer()
    : Renderer(core::toBase(RendererType::Enum::IDX_DEF)) {
  registerTechnique(this->commandQueue_);

  auto tech = std::make_shared<Technique>("deferred");
  RenderModule::getInternalContext()->techniqueMngr->get("deferred").value()(*tech, (struct TechniqueMetadata){});
  setTechnique(tech);
}

void DeferredRenderer::render() {}

NS_END()  // namespace experience
}  // namespace sway::render
