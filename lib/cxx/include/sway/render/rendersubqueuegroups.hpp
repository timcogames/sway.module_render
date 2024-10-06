#ifndef SWAY_RENDER_RENDERSUBQUEUEGROUPS_HPP
#define SWAY_RENDER_RENDERSUBQUEUEGROUPS_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

enum class RenderSubqueueGroup : u32_t {
  OPAQUE,  // Отрисовывать только непрозрачные части.
  TRANSPARENT,  // Отрисовывать только прозрачные части.
  Latest
};

#define RENDER_SUBQUEUE_GROUP_COUNT (core::detail::toBase(RenderSubqueueGroup::Latest))

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERSUBQUEUEGROUPS_HPP
