#ifndef SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINEDESCRIPTOR_HPP
#define SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINEDESCRIPTOR_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct GraphicsPipelineDescriptor {
  u32_t topology;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINEDESCRIPTOR_HPP
