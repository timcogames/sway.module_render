#ifndef SWAY_RENDER_EXPERIENCE_PASS_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_PASS_TYPEDEFS_HPP

#include <sway/render/experience/utility/cache.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Pass;
namespace PassTypedefs {
using Ptr_t = Pass *;
using UniquePtr_t = std::unique_ptr<Pass>;
using SharedPtr_t = std::shared_ptr<Pass>;
}  // namespace PassTypedefs

namespace PassCacheTypedefs {
using UniquePtr_t = std::unique_ptr<Cache>;
}  // namespace PassCacheTypedefs

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PASS_TYPEDEFS_HPP
