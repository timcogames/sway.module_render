#include <sway/render/spritesheet.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

SpriteSheet::SpriteSheet(nlohmann::json jobject) { parseAnimations(jobject); }

void SpriteSheet::parseAnimations(nlohmann::json jobject) {
  auto clips = jobject["animations"];
  if (!clips.is_object()) {
    return;
  }

  for (auto &clip : clips.get<nlohmann::json::object_t>()) {
    auto frames = clip.second.get<std::vector<std::string>>();
    parseFrames(jobject, clip.first, frames);
  }
}

void SpriteSheet::parseFrames(nlohmann::json jobject, std::string clipname, std::vector<std::string> framenames) {
  auto frames = jobject["frames"];
  if (!frames.is_array()) {
    return;
  }

  for (auto &frame : frames.get<std::vector<nlohmann::json::object_t>>()) {
    auto framename = frame["key"].get<std::string>();
    auto iter = std::find(framenames.begin(), framenames.end(), framename);
    if (iter != framenames.end()) {
      if (hasAnimation(clipname)) {
        SpriteAnimation anim = getAnimation(clipname).value();
        anim.clip_->addFrame(0, frame["rect"].get<nlohmann::json::object_t>(), false);
      } else {
        auto animClip = std::make_shared<SpriteAnimationClip<SpriteSheetFrame>>(clipname);
        animClip->addFrame(0, frame["rect"].get<nlohmann::json::object_t>(), false);

        SpriteAnimation anim;
        anim.setAnimationClip(animClip);
        animations_.insert(std::pair<std::string, SpriteAnimation>(clipname, anim));
      }
    }
  }
}

auto SpriteSheet::getAnimation(const std::string &name) const -> const std::optional<SpriteAnimation> & {
  const auto &iter = animations_.find(name);
  if (iter == animations_.end()) {
    return std::nullopt;
  }

  return (*iter).second;
}

auto SpriteSheet::hasAnimation(const std::string &name) const -> bool {
  return animations_.find(name) != animations_.end();
}

NS_END()  // namespace render
NS_END()  // namespace sway
