
#include <sway/render/experience/command/specs/beginpasscommand.hpp>
#include <sway/render/experience/command/specs/beginpasscommandhandler.hpp>
#include <sway/render/experience/command/specs/drawcommand.hpp>
#include <sway/render/experience/command/specs/drawcommandhandler.hpp>
#include <sway/render/experience/command/specs/endpasscommand.hpp>
#include <sway/render/experience/command/specs/endpasscommandhandler.hpp>
#include <sway/render/experience/pass/specs/graphicspass.hpp>
#include <sway/render/experience/pass/specs/scenegeompass.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/renderer/specs/forwardrenderer.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/technique/techniquemanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

ForwardRenderer::ForwardRenderer()
    : Renderer(core::detail::toBase(RendererType::Enum::IDX_FWD)) {
  auto ctx = RenderModule::getInternalContext();
  ctx->techniqueMngr->registerTech("forward", [&](Technique &tech, const TechniqueMetadata &meta) {
    // Pass 1: Depth prepass
    {
      auto pass = tech.passes()->getOrCreate<GraphicsPass>((struct PassDescriptor){.format = 1});
    }
    // Pass 2: Opaque/Transparent objects
    {
      auto pass = tech.passes()->getOrCreate<SceneGeomPass>((struct PassDescriptor){.format = 2});
      pass->setQueue(std::move(commandQueue_));
      pass->setup();
    }
  });

  auto tech = std::make_shared<Technique>("forward");
  ctx->techniqueMngr->get("forward").value()(*tech, (struct TechniqueMetadata){});
  setTechnique(tech);
}

void ForwardRenderer::render() {
  technique_->passes()->getOrCreate<SceneGeomPass>((struct PassDescriptor){.format = 2})->render();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
