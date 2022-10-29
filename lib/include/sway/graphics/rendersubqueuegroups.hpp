#ifndef SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_HPP
#define SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

enum class RenderSubqueueGroup_t : u32_t {
  kOpaque, /*!< Отрисовывать только непрозрачные части. */
  kTransparent, /*!< Отрисовывать только прозрачные части. */
  kLast
};

#define RENDER_SUBQUEUE_GROUP_COUNT (core::detail::toUnderlying(RenderSubqueueGroup_t::kLast))

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif
