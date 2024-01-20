#ifndef SWAY_RENDER_SPRITEANIMATIONCLIP_HPP
#define SWAY_RENDER_SPRITEANIMATIONCLIP_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/spriteanimationmodes.hpp>

#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct SpriteSheetFrame {
  math::rect4f_t rect;
};

struct SpriteFrame {
  std::string texture;
};

template <typename TYPE>
struct SpriteAnimationClip {
  std::vector<TYPE> frames;
  SpriteAnimationMode mode;
  std::string name;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_SPRITEANIMATIONCLIP_HPP
