#ifndef SWAY_RENDER_RENDERSUBQUEUEGROUPS_HPP
#define SWAY_RENDER_RENDERSUBQUEUEGROUPS_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

enum class RenderSubqueueGroup : u32_t {
  OPAQUE,  // Отрисовывать только непрозрачные части.
  TRANSPARENT,  // Отрисовывать только прозрачные части.
  Latest
};

#define RENDER_SUBQUEUE_GROUP_COUNT (core::detail::toBase(RenderSubqueueGroup::Latest))

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERSUBQUEUEGROUPS_HPP
