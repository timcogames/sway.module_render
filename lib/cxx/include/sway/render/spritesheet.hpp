#ifndef SWAY_RENDER_SPRITESHEET_HPP
#define SWAY_RENDER_SPRITESHEET_HPP

#include <sway/core.hpp>
#include <sway/render/spriteanimation.hpp>

#include <nlohmann/json.hpp>
#include <optional>
#include <unordered_map>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class SpriteSheet {
public:
  SpriteSheet(nlohmann::json jobject);

  ~SpriteSheet() = default;

  void parseAnimations(nlohmann::json jobject);

  void parseFrames(nlohmann::json jobject, std::string clipname, std::vector<std::string> framenames);

  [[nodiscard]]
  auto getAnimation(const std::string &name) const -> const std::optional<SpriteAnimation> &;

  [[nodiscard]]
  auto hasAnimation(const std::string &name) const -> bool;

  std::unordered_map<std::string, SpriteAnimation> animations_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_SPRITESHEET_HPP
