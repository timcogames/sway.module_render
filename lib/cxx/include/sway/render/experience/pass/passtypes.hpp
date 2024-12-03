#ifndef SWAY_RENDER_EXPERIENCE_PASSTYPES_HPP
#define SWAY_RENDER_EXPERIENCE_PASSTYPES_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

DECLARE_ENUM(PassType, GRAPHICS, COMPUTE, RESOURCE)

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PASSTYPES_HPP