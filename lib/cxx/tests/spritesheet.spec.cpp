#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>

#include <nlohmann/json.hpp>

#undef None
#undef Bool

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace sway;

std::string data{R"(
    {
      "metadata": {
        "image": "character.png",
        "size": { "w": 1922, "h": 1246 },
        "format": "RGBA8888"
      },
      "animations": {
        "character/idle": [ "character/idle_01.png", "character/idle_02.png" ]
      },
      "repeat": -1,
      "frame_rate": 8,
      "frames": [{
        "key": "character/idle_01.png",
        "rect": { "x": 0, "y": 0, "w": 32, "h": 32 },
        "rotated": false,
        "trimmed": true,
        "anchor": { "x": 0, "y": 0 }
      }, {
        "key": "character/idle_02.png",
        "rect": { "x": 0, "y": 0, "w": 32, "h": 32 },
        "rotated": false,
        "trimmed": true,
        "anchor": { "x": 0, "y": 0 }
      }]
    }
  )"};

TEST(SpriteAnimationClip, test) {
  render::SpriteAnimationClip<render::SpriteSheetFrame> clip("idle");
  clip.setMode(render::SpriteAnimationMode::ONCE);
  clip.addFrame(0, 0, 0, 32, 32, false);
}

// TEST(SpriteSheet, test2) {
//   auto sheet = std::make_shared<render::SpriteSheet>(nlohmann::json::parse(data));
//   ASSERT_EQ(sheet->animations_.size(), 1);
//   ASSERT_EQ(sheet->animations_[0].clip_->size(), 2);
// }
