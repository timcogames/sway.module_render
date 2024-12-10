#ifndef SWAY_RENDER_SPRITE_TYPEDEFS_HPP
#define SWAY_RENDER_SPRITE_TYPEDEFS_HPP

#include <sway/core.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Sprite;
namespace SpriteTypedefs {
using SharedPtr_t = std::shared_ptr<Sprite>;
}  // namespace SpriteTypedefs

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_SPRITE_TYPEDEFS_HPP
