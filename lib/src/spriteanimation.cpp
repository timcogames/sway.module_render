#include <sway/render/spriteanimation.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

SpriteAnimation::SpriteAnimation()
    : frameSize_(math::size2f_zero)
    , currentFrameIdx_(0)
    , frameTime_(0.1F)
    , timeCounter_(0.0F) {}

void SpriteAnimation::update_(f32_t deltaTime) {
  timeCounter_ += deltaTime;
  if (timeCounter_ > frameTime_) {
    currentFrameIdx_ = (currentFrameIdx_ + 1) % clip_.frames.size();
    timeCounter_ = 0;
  }

  auto currentFrame = clip_.frames[currentFrameIdx_];
  auto currentFrameRect = math::rect4f_t(0.0F, 0.0F, frameSize_.getW(), frameSize_.getH());

  this->updateGeometryUV(getMaterial()->getImageSize(),
      currentFrameRect.offset(currentFrame.getX() * frameSize_.getW(), currentFrame.getY() * frameSize_.getH()));
}

void SpriteAnimation::onUpdate(math::mat4f_t transform, math::mat4f_t proj, f32_t deltaTime) {
  update_(deltaTime);
  Sprite::onUpdate(transform, proj, deltaTime);
}

void SpriteAnimation::setAnimationClip(const SpriteAnimationClip &clip) { clip_ = clip; }

void SpriteAnimation::play() {}

void SpriteAnimation::playAtFrame(s32_t idx) {}

void SpriteAnimation::replay() {}

void SpriteAnimation::pause() {}

void SpriteAnimation::stop() {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
