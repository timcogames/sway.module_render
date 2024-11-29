#ifndef SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINE_HPP
#define SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINE_HPP

#include <sway/core.hpp>
#include <sway/render/experience/pipeline/_typedefs.hpp>
#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/experience/pipeline/pipelinedescriptor.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class GraphicsPipeline : public Pipeline {
public:
#pragma region "Ctors/Dtor"

  GraphicsPipeline(const PipelineDescriptor &desc)
      : Pipeline(desc) {}

  DTOR_VIRTUAL_DEFAULT(GraphicsPipeline);

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINE_HPP
