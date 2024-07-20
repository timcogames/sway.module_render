#ifndef SWAY_RENDER_SPRITEANIMATION_HPP
#define SWAY_RENDER_SPRITEANIMATION_HPP

#include <sway/core.hpp>
#include <sway/render/sprite.hpp>
#include <sway/render/spriteanimationclip.hpp>
#include <sway/render/spriteanimationmodes.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

enum class AnimationStatus : s8_t { RUNNING, PAUSED, STOPPED };

class Animation {
public:
  inline static i32_t DFLT_NBR_CYCLES = 1;

  Animation()
      : status_(AnimationStatus::STOPPED)
      , cycles_(DFLT_NBR_CYCLES)
      , reversed_(false)
      , paused_(false) {}

  virtual ~Animation() = default;

  MTHD_VIRTUAL(void play()) { paused_ = false; }

  MTHD_VIRTUAL(void pause()) {
    if (paused_) {
      return;
    }

    paused_ = true;
  }

  MTHD_VIRTUAL(void stop()) {}

  void setStatus(AnimationStatus status) { status_ = status; }

  [[nodiscard]]
  auto getStatus() const -> AnimationStatus {
    return status_;
  }

  [[nodiscard]]
  auto isRunning() const -> bool {
    return status_ == AnimationStatus::RUNNING;
  }

  [[nodiscard]]
  auto isPaused() const -> bool {
    return status_ == AnimationStatus::PAUSED;
  }

  [[nodiscard]]
  auto isStopped() const -> bool {
    return status_ == AnimationStatus::STOPPED;
  }

private:
  AnimationStatus status_;
  i32_t cycles_;
  bool reversed_;
  bool paused_;
};

class SpriteAnimation : public Sprite, public Animation {
public:
  DECLARE_CLASS_METADATA(SpriteAnimation, Sprite)

  SpriteAnimation();

  virtual ~SpriteAnimation() = default;

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t deltaTime));

  MTHD_OVERRIDE(void play());

  MTHD_OVERRIDE(void pause());

  MTHD_OVERRIDE(void stop());

  void setAnimationClip(std::shared_ptr<SpriteAnimationClip<SpriteSheetFrame>> clip) { clip_ = clip; }

  void setFrameSize(const math::size2f_t &size) { frameSize_ = size; }

  void playAtFrame(i32_t idx) {}

  void replay() {}

private:
  void update_(f32_t dtime);

public:
  std::shared_ptr<SpriteAnimationClip<SpriteSheetFrame>> clip_;
  math::size2f_t frameSize_;
  i32_t currentFrameIdx_;
  f32_t frameTime_;
  f32_t timeCounter_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_SPRITEANIMATION_HPP
