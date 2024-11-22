#ifndef SWAY_RENDER_EXPERIENCE_CACHEITEM_HPP
#define SWAY_RENDER_EXPERIENCE_CACHEITEM_HPP

#include <sway/render/experience/base/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

template <class TYPE>
struct CacheItem {
  std::size_t hash;
  DisposableTypedefs::UniquePtr_t data;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_CACHEITEM_HPP
