#ifndef SWAY_RENDER_EXPERIENCE_PIPELINELIBRARY_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINELIBRARY_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/pipeline/_typedefs.hpp>
#include <sway/render/experience/pipeline/specs/graphicspipeline.hpp>
#include <sway/render/experience/pipeline/specs/graphicspipelinedescriptor.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

class PipelineLibrary {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  PipelineLibrary();

  DTOR_DEFAULT(PipelineLibrary);

  /** @} */
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
}  // namespace sway::render

#include <sway/render/experience/pipeline/pipelinelibrary.inl>

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINELIBRARY_HPP
