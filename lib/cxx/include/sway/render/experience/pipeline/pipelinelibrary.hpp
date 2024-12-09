#ifndef SWAY_RENDER_EXPERIENCE_PIPELINELIBRARY_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINELIBRARY_HPP

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

class PipelineLibrary {
public:
#pragma region "Ctors/Dtor"

  PipelineLibrary();

  DTOR_DEFAULT(PipelineLibrary);

#pragma endregion

  auto getGraphicsPipeline(const GraphicsPipelineDescriptor &desc) -> GraphicsPipelineTypedefs::SharedFuture_t;

private:
  GraphicsPipelineTypedefs::Container_t pipelines_;
};

/**
 * end of pipeline group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#include <sway/render/experience/pipeline/pipelinelibrary.inl>

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINELIBRARY_HPP
