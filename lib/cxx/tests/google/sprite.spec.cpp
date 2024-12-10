#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>

#include <nlohmann/json.hpp>

#undef None
#undef Bool

#include <gmock/gmock.h>
#include <gtest/gtest.h>

NS_SHORT_SWAY()

TEST(Sprite, test) {
  render::Sprite sprite;
  sprite.initialize(nullptr, nullptr, math::size2f_t(32, 32), math::size2i_one);
  // sprite.setRenderQueue(nullptr);
}
