#ifndef SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_HPP
#define SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

enum class RenderSubqueueGroup : u32_t {
  OPAQUE,  // Отрисовывать только непрозрачные части.
  TRANSPARENT,  // Отрисовывать только прозрачные части.
  LATEST
};

#define RENDER_SUBQUEUE_GROUP_COUNT (core::detail::toUnderlying(RenderSubqueueGroup::LATEST))

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_HPP
