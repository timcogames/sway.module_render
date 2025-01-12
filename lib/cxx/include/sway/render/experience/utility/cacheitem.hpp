#ifndef SWAY_RENDER_EXPERIENCE_CACHEITEM_HPP
#define SWAY_RENDER_EXPERIENCE_CACHEITEM_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/utility/_typedefs.hpp>

namespace sway::render {
NS_BEGIN(experience)

struct CacheItem {
  std::size_t hash;
  CacheableTypedefs::UniquePtr_t data;
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_CACHEITEM_HPP
