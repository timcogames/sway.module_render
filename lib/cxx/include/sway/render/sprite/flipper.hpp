#ifndef SWAY_RENDER_FLIPPER_HPP
#define SWAY_RENDER_FLIPPER_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

enum class Flipper : u32_t { NONE = 0, HORZ, VERT, Latest };

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_FLIPPER_HPP
