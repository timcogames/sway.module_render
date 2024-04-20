#include <sway/render/spriteanimation.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

SpriteAnimation::SpriteAnimation()
    : clip_(nullptr)
    , frameSize_(math::size2f_zero)
    , currentFrameIdx_(0)
    , frameTime_(0.1F)
    , timeCounter_(0.0F)
    , playing_(false) {}

void SpriteAnimation::update_(f32_t dtime) {
  if (!playing_) {
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
  this->updateGeometryUV(getMaterial()->getImages()[0].second->getSize(), frame->rect);
}

void SpriteAnimation::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtime) {
  update_(dtime);
  Sprite::onUpdate(tfrm, proj, view, dtime);
}

void SpriteAnimation::play() { playing_ = true; }

void SpriteAnimation::playAtFrame(s32_t idx) {}

void SpriteAnimation::replay() {}

void SpriteAnimation::pause() { playing_ = false; }

void SpriteAnimation::stop() {
  playing_ = false;
  currentFrameIdx_ = 0;
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
