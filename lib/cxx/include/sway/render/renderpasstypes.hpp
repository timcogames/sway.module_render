#ifndef SWAY_RENDER_PASSTYPES_HPP
#define SWAY_RENDER_PASSTYPES_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

DECLARE_ENUM(PassType, SHADING, PRESENT, MANUAL)

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PASSTYPES_HPP
