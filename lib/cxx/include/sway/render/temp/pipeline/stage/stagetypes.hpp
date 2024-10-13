#ifndef SWAY_RENDER_STAGETYPES_HPP
#define SWAY_RENDER_STAGETYPES_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

DECLARE_ENUM(StageType, IDX_COLOR, IDX_DEPTH, IDX_STENCIL)

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_STAGETYPES_HPP
