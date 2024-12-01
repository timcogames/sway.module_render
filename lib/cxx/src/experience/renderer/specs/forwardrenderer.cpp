
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
  ctx->techniqueMngr->registerTech("forward", [](Technique &tech, const TechniqueMetadata &meta) {
    // Pass 1: Depth prepass
    tech.passes()->getOrCreate<GraphicsPass>((struct PassDescriptor){.format = 1});
    // Pass 2: Opaque/Transparent objects
    tech.passes()->getOrCreate<SceneGeomPass>((struct PassDescriptor){.format = 2});
  });

  auto tech = std::make_shared<Technique>("forward");
  ctx->techniqueMngr->get("forward").value()(*tech, (struct TechniqueMetadata){});
  setTechnique(tech);
}

void ForwardRenderer::render() {}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
