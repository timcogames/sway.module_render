#ifndef SWAY_RENDER_PIPELINE_HPP
#define SWAY_RENDER_PIPELINE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/temp/pipeline/renderer.hpp>
#include <sway/render/temp/pipeline/stage/pass/subqueues/geompass.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Pipeline {
  DECLARE_CLASS_POINTER_ALIASES(Pipeline)

public:
#pragma region "Ctors/Dtor"

  Pipeline() {
    for (auto i = 0; i < RendererTypeCountWithoutNone; i++) {
      renderers_.push_back(std::make_shared<Renderer>(core::detail::toEnum<RendererType::Enum>(i)));
    }
  }

  DTOR_VIRTUAL_DEFAULT(Pipeline);

#pragma endregion

  void setup() {
    auto forward = getRenderer(RendererType::Enum::FORWARD);
    auto forwardStageQueue = forward->getStageQueue(StageGroupIndex::Enum::IDX_SHADING);
    auto forwardStage = forwardStageQueue.addStage();

    forwardStage->addPass(std::make_shared<GeomPass>("geom"));
  }

  void renderScene(PassType::Enum type) {
    auto forward = getRenderer(RendererType::Enum::FORWARD);
    auto forwardStageQueue = forward->getStageQueue(StageGroupIndex::Enum::IDX_SHADING).getStages();
  }

  void render() { renderScene(PassType::Enum::GEOM); }

  auto getRenderer(RendererType::Enum type) -> Renderer::SharedPtr_t {
    return *std::find_if(std::begin(renderers_), std::end(renderers_),
        [&](Renderer::SharedPtr_t renderer) { return renderer->type() == type; });
  }

private:
  Renderer::SharedPtrVec_t renderers_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PIPELINE_HPP
