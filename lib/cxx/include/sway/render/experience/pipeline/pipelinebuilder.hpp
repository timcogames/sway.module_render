#ifndef SWAY_RENDER_EXPERIENCE_PIPELINEBUILDER_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINEBUILDER_HPP

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

class PipelineBuilder {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  PipelineBuilder();

  DTOR_DEFAULT(PipelineBuilder);

  /** @} */
#pragma endregion

  static void createGraphicsPipeline(
      GraphicsPipelineTypedefs::Promise_t &&promise, const GraphicsPipelineDescriptor &desc);
};

/**
 * end of pipeline group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINEBUILDER_HPP
