#ifndef SWAY_RENDER_SPRITEANIMATIONCLIP_HPP
#define SWAY_RENDER_SPRITEANIMATIONCLIP_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/spriteanimationmodes.hpp>

#include <nlohmann/json.hpp>
#include <optional>
#include <unordered_map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct FrameMetadata {
  math::point2f_t anchor;
};

struct Frame {
  FrameMetadata metadata;
  bool flipped;
};

struct SpriteSheetFrame : public Frame {
  math::rect4f_t rect;
};

struct SpriteImageFrame : public Frame {
  std::string name;
};

template <typename FRAME_TYPE>
class SpriteAnimationClip {
public:
  SpriteAnimationClip(const std::string &name)
      : mode_(SpriteAnimationMode::ONCE)
      , name_(name) {}

  ~SpriteAnimationClip() = default;

  void addFrame(u32_t idx, nlohmann::json::object_t jrect, bool flipped) {
    addFrame(idx, jrect["x"], jrect["y"], jrect["w"], jrect["h"], flipped);
  }

  void addFrame(u32_t idx, int x, int y, int w, int h, bool flipped) {
    std::shared_ptr<FRAME_TYPE> frame = std::make_shared<FRAME_TYPE>();
    frame->rect = math::rect4f_t(x, y, x + w, y + h);
    frame->flipped = flipped;

    frames_.insert(std::make_pair(idx, frame));
  }

  auto getFrame(u32_t idx) const -> const std::optional<std::shared_ptr<FRAME_TYPE>> & {
    const auto &iter = frames_.find(idx);
    if (iter != frames_.end()) {
      return (*iter).second;
    }

    return std::nullopt;
  }

  [[nodiscard]]
  auto size() const -> u32_t {
    return static_cast<u32_t>(frames_.size());
  }

  void setMode(SpriteAnimationMode mode) { mode_ = mode; }

private:
  std::unordered_map<u32_t, std::shared_ptr<FRAME_TYPE>> frames_;
  SpriteAnimationMode mode_;
  std::string name_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_SPRITEANIMATIONCLIP_HPP
