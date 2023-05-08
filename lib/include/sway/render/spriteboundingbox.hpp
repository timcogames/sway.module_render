#ifndef SWAY_RENDER_SPRITEBOUNDINGBOX_HPP
#define SWAY_RENDER_SPRITEBOUNDINGBOX_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct SpriteBoundingBox {
  math::point2f_t min;
  math::point2f_t max;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_SPRITEBOUNDINGBOX_HPP
