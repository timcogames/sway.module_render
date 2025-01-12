#ifndef SWAY_RENDER_EXPERIENCE_COMPUTEPIPELINE_HPP
#define SWAY_RENDER_EXPERIENCE_COMPUTEPIPELINE_HPP

#include <sway/core.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/pipeline/_typedefs.hpp>
#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/experience/pipeline/specs/computepipelinedescriptor.hpp>
#include <sway/render/experience/pipeline/specs/computepipelinestate.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

class ComputePipeline : public Pipeline {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  ComputePipeline(const ComputePipelineDescriptor &desc)
      : descriptor_(desc) {}

  DTOR_VIRTUAL_DEFAULT(ComputePipeline);

  /** @} */
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
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_COMPUTEPIPELINE_HPP
