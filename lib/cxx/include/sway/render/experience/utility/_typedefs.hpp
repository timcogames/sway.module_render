#ifndef SWAY_RENDER_EXPERIENCE_BASE_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_BASE_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
NS_BEGIN(experience)

class Cacheable;
namespace CacheableTypedefs {
using UniquePtr_t = std::unique_ptr<Cacheable>;
}  // namespace CacheableTypedefs

struct CacheItem;
namespace CacheItemTypedefs {
using Container_t = std::vector<CacheItem>;
}  // namespace CacheItemTypedefs

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_BASE_TYPEDEFS_HPP
