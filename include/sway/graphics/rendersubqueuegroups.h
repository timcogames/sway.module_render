#ifndef SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_H
#define SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_H

#include <sway/core.h>

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

#endif // SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_H
