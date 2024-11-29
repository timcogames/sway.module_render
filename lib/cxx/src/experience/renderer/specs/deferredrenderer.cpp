
#include <sway/render/experience/pass/specs/graphicspass.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/renderer/specs/deferredrenderer.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/technique/techniquemanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

DeferredRenderer::DeferredRenderer()
    : Renderer(core::detail::toBase(RendererType::Enum::IDX_DEF)) {
  auto ctx = RenderModule::getInternalContext();
  ctx->techniqueMngr->registerTech("deferred", [](Technique &tech, const TechniqueMetadata &meta) {});

  auto tech = std::make_shared<Technique>();
  ctx->techniqueMngr->get("deferred").value()(*tech, (struct TechniqueMetadata){});
  setTechnique(tech);
}

void DeferredRenderer::render() {}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
