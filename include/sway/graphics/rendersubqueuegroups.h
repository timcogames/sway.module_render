#ifndef SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_H
#define SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_H

#include <sway/core.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

enum RenderSubqueueGroups {
	kRenderSubqueueGroup_Opaque      = 0, /*!< Отрисовывать только непрозрачные части. */
	kRenderSubqueueGroup_Transparent = 1  /*!< Отрисовывать только прозрачные части. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERSUBQUEUEGROUPS_H
