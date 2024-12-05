#ifndef SWAY_RENDER_EXPERIENCE_COMPUTEPIPELINE_HPP
#define SWAY_RENDER_EXPERIENCE_COMPUTEPIPELINE_HPP

#include <sway/core.hpp>
#include <sway/render/experience/pipeline/_typedefs.hpp>
#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/experience/pipeline/specs/computepipelinedescriptor.hpp>
#include <sway/render/experience/pipeline/specs/computepipelinestate.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

class ComputePipeline : public Pipeline {
public:
#pragma region "Ctors/Dtor"

  ComputePipeline(const ComputePipelineDescriptor &desc)
      : descriptor_(desc) {}

  DTOR_VIRTUAL_DEFAULT(ComputePipeline);

#pragma endregion

private:
  ComputePipelineDescriptor descriptor_;
  ComputePipelineState state_;
};

/**
 * end of pipeline group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMPUTEPIPELINE_HPP
