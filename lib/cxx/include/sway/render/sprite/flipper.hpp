#ifndef SWAY_RENDER_FLIPPER_HPP
#define SWAY_RENDER_FLIPPER_HPP

#include <sway/core.hpp>

namespace sway::render {

enum class Flipper : u32_t { NONE = 0, HORZ, VERT, Latest };

}  // namespace sway::render

#endif  // SWAY_RENDER_FLIPPER_HPP
