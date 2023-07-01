#ifndef SWAY_RENDER_SPRITEANIMATION_HPP
#define SWAY_RENDER_SPRITEANIMATION_HPP

#include <sway/core.hpp>
#include <sway/render/sprite.hpp>
#include <sway/render/spriteanimationclip.hpp>
#include <sway/render/spriteanimationmodes.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class SpriteAnimation : public Sprite {
public:
  DECLARE_CLASS_METADATA(SpriteAnimation, Sprite)

  SpriteAnimation();

  ~SpriteAnimation() = default;

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t transform, math::mat4f_t proj, math::mat4f_t view, f32_t deltaTime));

  void setAnimationClip(const SpriteAnimationClip &clip);

  void setFrameSize(const math::size2f_t &size) { frameSize_ = size; }

  void update_(f32_t deltaTime);

  void play();

  void playAtFrame(s32_t idx);

  void replay();

  void pause();

  void stop();

private:
  SpriteAnimationClip clip_;
  math::size2f_t frameSize_;
  s32_t currentFrameIdx_;
  f32_t frameTime_;
  f32_t timeCounter_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_SPRITEANIMATION_HPP
