#ifndef SWAY_RENDER_EXPERIENCE_PIPELINESTATE_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINESTATE_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct PipelineState {
  bool depthTest = false;
  bool depthWriteMask = true;
  bool stencilTest = false;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINESTATE_HPP
