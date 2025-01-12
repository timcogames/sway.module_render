#ifndef SWAY_RENDER_EXPERIENCE_CACHE_HPP
#define SWAY_RENDER_EXPERIENCE_CACHE_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/utility/_typedefs.hpp>
#include <sway/render/experience/utility/cacheitem.hpp>

namespace sway::render {
NS_BEGIN(experience)

class Cache {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Cache();

  DTOR(Cache);

  /** @} */
#pragma endregion

  template <typename TYPE, typename DESC>
  auto getOrCreate(const DESC &desc) -> TYPE *;

  auto getItems() -> CacheItemTypedefs::Container_t & { return items_; }

private:
  CacheItemTypedefs::Container_t items_;
};

NS_END()  // namespace experience
}  // namespace sway::render

#include <sway/render/experience/utility/cache.inl>

#endif  // SWAY_RENDER_EXPERIENCE_CACHE_HPP
