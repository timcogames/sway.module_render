#include <sway/render/experience/pass/specs/graphicspass.hpp>
#include <sway/render/experience/pass/specs/scenegeompass.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/technique/delegates/defer.hpp>
#include <sway/render/experience/technique/techniquemanager.hpp>

namespace sway::render {
NS_BEGIN(experience)

void DeferTechniqueDelegate::create(Technique &tech, const TechniqueMetadata &meta) {
  // Pass 1: Depth prepass
  {
    // auto pass = tech.getPasses()->getOrCreate<GraphicsPass>((struct PassDescriptor){.format = 1});
    // pass->setQueue(std::move(queue));
    // pass->prepare();
  }
  // Pass 2: Opaque/Transparent objects
  {
    // auto pass = tech.getPasses()->getOrCreate<SceneGeomPass>((struct PassDescriptor){.format = 2});
    // pass->setQueue(std::move(queue));
    // pass->prepare();
  }
}

NS_END()  // namespace experience
}  // namespace sway::render
