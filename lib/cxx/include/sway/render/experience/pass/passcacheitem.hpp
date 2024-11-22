#ifndef SWAY_RENDER_EXPERIENCE_PASSCACHEITEM_HPP
#define SWAY_RENDER_EXPERIENCE_PASSCACHEITEM_HPP

#include <sway/render/experience/pass/_typedefs.hpp>
#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct PassCacheItem {
  std::size_t hash;
  PassTypedefs::UniquePtr_t pass;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PASSCACHEITEM_HPP
