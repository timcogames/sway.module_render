#ifndef SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINESTATE_HPP
#define SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINESTATE_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
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
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINESTATE_HPP
