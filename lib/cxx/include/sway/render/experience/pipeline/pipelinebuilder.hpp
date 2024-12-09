#ifndef SWAY_RENDER_EXPERIENCE_PIPELINEBUILDER_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINEBUILDER_HPP

#include <sway/render/experience/pipeline/_typedefs.hpp>
#include <sway/render/experience/pipeline/specs/graphicspipeline.hpp>
#include <sway/render/experience/pipeline/specs/graphicspipelinedescriptor.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

class PipelineBuilder {
public:
#pragma region "Ctors/Dtor"

  PipelineBuilder();

  DTOR_DEFAULT(PipelineBuilder);

#pragma endregion

  static void createGraphicsPipeline(
      GraphicsPipelineTypedefs::Promise_t &&promise, const GraphicsPipelineDescriptor &desc);
};

/**
 * end of pipeline group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINEBUILDER_HPP
