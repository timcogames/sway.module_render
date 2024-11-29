#ifndef SWAY_RENDER_EXPERIENCE_PIPELINE_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINE_HPP

#include <sway/render/experience/pipeline/pipelinedescriptor.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Pipeline {
public:
#pragma region "Ctors/Dtor"

  Pipeline(const PipelineDescriptor &desc);

  DTOR_DEFAULT(Pipeline);

#pragma endregion

  void initialize();
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINE_HPP
