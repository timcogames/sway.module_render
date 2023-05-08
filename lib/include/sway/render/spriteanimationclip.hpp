#ifndef SWAY_RENDER_SPRITEANIMATIONCLIP_HPP
#define SWAY_RENDER_SPRITEANIMATIONCLIP_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/spriteanimationmodes.hpp>

#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct SpriteAnimationClip {
  std::vector<math::point2f_t> frames;
  SpriteAnimationMode mode;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_SPRITEANIMATIONCLIP_HPP
