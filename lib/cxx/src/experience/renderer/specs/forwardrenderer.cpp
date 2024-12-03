#include <sway/render/experience/pass/specs/graphicspass.hpp>
#include <sway/render/experience/pass/specs/scenegeompass.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/renderer/specs/forwardrenderer.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/technique/techniquemanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void ForwardRenderer::registerTechnique(CommandQueueTypedefs::UniquePtr_t &queue) {
  // clang-format off
  RenderModule::getInternalContext()->techniqueMngr->registerTechnique("forward", 
    [&](Technique &tech, const TechniqueMetadata &meta) {
        // Pass 1: Depth prepass
        {
          auto pass = tech.getPasses()->getOrCreate<GraphicsPass>((struct PassDescriptor){.format = 1});
        }
        // Pass 2: Opaque/Transparent objects
        {
          auto pass = tech.getPasses()->getOrCreate<SceneGeomPass>((struct PassDescriptor){.format = 2});
          pass->setQueue(std::move(queue));
          pass->setup();
        }
    });
  // clang-format on
}

ForwardRenderer::ForwardRenderer()
    : Renderer(core::detail::toBase(RendererType::Enum::IDX_FWD)) {
  registerTechnique(this->commandQueue_);

  auto tech = std::make_shared<Technique>("forward");
  RenderModule::getInternalContext()->techniqueMngr->get("forward").value()(*tech, {});
  setTechnique(tech);
}

void ForwardRenderer::render() {
  technique_->getPasses()->getOrCreate<SceneGeomPass>((struct PassDescriptor){.format = 2})->render();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
