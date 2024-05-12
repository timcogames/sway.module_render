#ifndef SWAY_RENDER_FLIPPER_HPP
#define SWAY_RENDER_FLIPPER_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

enum class Flipper : u32_t { NONE = 0, HORZ, VERT, Latest };

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_FLIPPER_HPP
