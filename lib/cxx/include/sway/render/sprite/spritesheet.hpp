#ifndef SWAY_RENDER_SPRITESHEET_HPP
#define SWAY_RENDER_SPRITESHEET_HPP

#include <sway/core.hpp>
#include <sway/render/sprite/spriteanimation.hpp>

#include <nlohmann/json.hpp>
#include <optional>
#include <unordered_map>

namespace sway::render {

class SpriteSheet {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  SpriteSheet(nlohmann::json jobject);

  DTOR_DEFAULT(SpriteSheet);

  /** @} */
#pragma endregion

  void parseAnimations(nlohmann::json jobject);

  void parseFrames(nlohmann::json jobject, std::string clipname, std::vector<std::string> framenames);

  [[nodiscard]] auto getAnimation(const std::string &name) const -> const std::optional<SpriteAnimation> &;

  [[nodiscard]] auto hasAnimation(const std::string &name) const -> bool;

  std::unordered_map<std::string, SpriteAnimation> animations_;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_SPRITESHEET_HPP
