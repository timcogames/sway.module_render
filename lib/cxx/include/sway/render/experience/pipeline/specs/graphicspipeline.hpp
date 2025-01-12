#ifndef SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINE_HPP
#define SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINE_HPP

#include <sway/core.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/pipeline/_typedefs.hpp>
#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/experience/pipeline/specs/graphicspipelinedescriptor.hpp>
#include <sway/render/experience/pipeline/specs/graphicspipelinestate.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

/**
 * \~russian @brief Этот неизменяемый объект содержит информацию, необходимую для построения шейдерной программы
 *   и установки состояния API для отрисовки.
 */
class GraphicsPipeline : public Pipeline {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  GraphicsPipeline(const GraphicsPipelineDescriptor &desc)
      : descriptor_(desc) {}

  DTOR_VIRTUAL_DEFAULT(GraphicsPipeline);

  /** @} */
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
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINE_HPP
