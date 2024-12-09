#ifndef SWAY_RENDER_EXPERIENCE_TECHNIQUEDELEGATE_HPP
#define SWAY_RENDER_EXPERIENCE_TECHNIQUEDELEGATE_HPP

#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class TechniqueDelegate {
public:
  // PURE_VIRTUAL(auto getPipelineDescriptor() -> GraphicsPipelineDescriptor::SharedPtr_t);
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_TECHNIQUEDELEGATE_HPP
