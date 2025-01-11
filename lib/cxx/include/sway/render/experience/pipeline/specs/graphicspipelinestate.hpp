#ifndef SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINESTATE_HPP
#define SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINESTATE_HPP

#include <sway/render/_stdafx.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

struct GraphicsPipelineState {
  bool depthTest = false;
  bool depthWriteMask = true;
  bool stencilTest = false;
};

/**
 * end of pipeline group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINESTATE_HPP
