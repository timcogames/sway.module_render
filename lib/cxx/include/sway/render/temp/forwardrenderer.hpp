#ifndef SWAY_RENDER_FORWARDRENDERER_HPP
#define SWAY_RENDER_FORWARDRENDERER_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/temp/pipeline.hpp>
#include <sway/render/temp/pipeline/stage/pass/subqueues/geompass.hpp>
#include <sway/render/temp/renderertypes.hpp>

#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class ForwardRenderer : public Renderer {
public:
#pragma region "Ctors/Dtor"

  ForwardRenderer()
      : Renderer(core::detail::toBase(RendererType::Enum::FORWARD)) {}

  DTOR_VIRTUAL(ForwardRenderer) {}

#pragma endregion

  void setup() {
    auto stageQueue = pipeline_->getStageQueue(StageGroupIndex::Enum::IDX_SHADING);
    auto stage = stageQueue.addStage();

    stage->addPass(std::make_shared<GeomPass>("geom"));
  }

private:
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_FORWARDRENDERER_HPP
