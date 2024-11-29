#ifndef SWAY_RENDER_EXPERIENCE_BASE_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_BASE_TYPEDEFS_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Cacheable;
namespace CacheableTypedefs {
using UniquePtr_t = std::unique_ptr<Cacheable>;
}  // namespace CacheableTypedefs

// clang-format off
template <typename TYPE> struct CacheItem;
namespace CacheItemTypedefs {
template <typename TYPE> using Container_t = std::vector<CacheItem<TYPE>>;
}  // namespace CacheItemTypedefs
// clang-format on

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_BASE_TYPEDEFS_HPP
