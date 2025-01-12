#ifndef SWAY_RENDER_SPRITE_TYPEDEFS_HPP
#define SWAY_RENDER_SPRITE_TYPEDEFS_HPP

#include <sway/core.hpp>

#include <memory>

namespace sway::render {

class Sprite;
namespace SpriteTypedefs {
using SharedPtr_t = std::shared_ptr<Sprite>;
}  // namespace SpriteTypedefs

}  // namespace sway::render

#endif  // SWAY_RENDER_SPRITE_TYPEDEFS_HPP
