#include <sway/render/spriteanimation.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

SpriteAnimation::SpriteAnimation()
    : clip_(nullptr)
    , frameSize_(math::size2f_zero)
    , currentFrameIdx_(0)
    , frameTime_(0.1F)
    , timeCounter_(0.0F) {}

void SpriteAnimation::update_(f32_t dtime) {
  if (this->getStatus() != AnimationStatus::RUNNING) {
    return;
  }

  timeCounter_ += dtime;
  if (timeCounter_ > frameTime_) {
    currentFrameIdx_ = (currentFrameIdx_ + 1) % clip_->size();
    timeCounter_ = 0;
  }

  auto frameOptional = clip_->getFrame(currentFrameIdx_);
  if (!frameOptional.has_value()) {
    return;
  }

  auto frame = frameOptional.value();
  this->updateGeometryUV(getMaterial()->getImage(0 /* ALBEDO */)->getSize(), frame->rect);
}

void SpriteAnimation::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime) {
  update_(dtime);
  Sprite::onUpdate(tfrm, proj, view, dtime);
}

void SpriteAnimation::play() { this->setStatus(AnimationStatus::RUNNING); }

void SpriteAnimation::pause() { this->setStatus(AnimationStatus::PAUSED); }

void SpriteAnimation::stop() {
  this->setStatus(AnimationStatus::STOPPED);
  currentFrameIdx_ = 0;
}

NS_END()  // namespace render
NS_END()  // namespace sway
