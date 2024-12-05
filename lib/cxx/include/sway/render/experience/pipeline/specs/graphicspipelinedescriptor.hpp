#ifndef SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINEDESCRIPTOR_HPP
#define SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINEDESCRIPTOR_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

struct GraphicsPipelineDescriptor {
  u32_t vso;  ///< Vertex shader
  u32_t gso;  ///< Geometry shader
  u32_t fso;  ///< Fragment shader
  u32_t topology;
};

/**
 * end of pipeline group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINEDESCRIPTOR_HPP
