#ifndef SWAY_RENDER_EXPERIENCE_TECHNIQUEDELEGATE_HPP
#define SWAY_RENDER_EXPERIENCE_TECHNIQUEDELEGATE_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>

namespace sway::render {
NS_BEGIN(experience)

class TechniqueDelegate {
public:
  // PURE_VIRTUAL(auto getPipelineDescriptor() -> GraphicsPipelineDescriptor::SharedPtr_t);
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_TECHNIQUEDELEGATE_HPP
