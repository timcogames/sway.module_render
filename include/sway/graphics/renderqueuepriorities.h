#ifndef SWAY_GRAPHICS_RENDERQUEUEPRIORITIES_H
#define SWAY_GRAPHICS_RENDERQUEUEPRIORITIES_H

#include <sway/core.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

/*!
 * \brief
 *    Перечисление приоритетов.
 */
enum RenderQueuePriorities {
	kRenderQueuePriority_VeryLow  = 0, /*!< Очень низкий приоритет. */
	kRenderQueuePriority_Low      = 1, /*!< Низкий приоритет. */
	kRenderQueuePriority_Normal   = 2, /*!< Средний приоритет. */
	kRenderQueuePriority_High     = 3, /*!< Высокий приоритет. */
	kRenderQueuePriority_VeryHigh = 4  /*!< Очень высокий приоритет. */
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_RENDERQUEUEPRIORITIES_H
