#ifndef SWAY_RENDER_EXPERIENCE_CACHE_HPP
#define SWAY_RENDER_EXPERIENCE_CACHE_HPP

#include <sway/render/experience/base/_typedefs.hpp>
#include <sway/render/experience/base/cacheitem.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

template <class TYPE>
class Cache {
public:
#pragma region "Ctors/Dtor"

  Cache() = default;

  DTOR(Cache);

#pragma endregion

  template <typename DESC, typename RET>
  auto getOrCreate(const DESC &desc) -> RET *;

private:
  CacheItemTypedefs::Container_t<TYPE> items_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#include <sway/render/experience/base/cache.inl>

#endif  // SWAY_RENDER_EXPERIENCE_CACHE_HPP
