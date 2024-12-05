#ifndef SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINE_HPP
#define SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINE_HPP

#include <sway/core.hpp>
#include <sway/render/experience/pipeline/_typedefs.hpp>
#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/experience/pipeline/specs/graphicspipelinedescriptor.hpp>
#include <sway/render/experience/pipeline/specs/graphicspipelinestate.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

/**
 * \~russian @brief Этот неизменяемый объект содержит информацию, необходимую для построения шейдерной программы
 *                  и установки состояния API для отрисовки.
 */
class GraphicsPipeline : public Pipeline {
public:
#pragma region "Ctors/Dtor"

  GraphicsPipeline(const GraphicsPipelineDescriptor &desc)
      : descriptor_(desc) {}

  DTOR_VIRTUAL_DEFAULT(GraphicsPipeline);

#pragma endregion

private:
  GraphicsPipelineDescriptor descriptor_;
  GraphicsPipelineState state_;
};

/**
 * end of pipeline group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINE_HPP
