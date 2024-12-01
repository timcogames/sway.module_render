#ifndef SWAY_RENDER_EFFECTRESOURCE_HPP
#define SWAY_RENDER_EFFECTRESOURCE_HPP

#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

struct EffectResource final {
  std::string name;
  std::size_t hash;
  std::atomic_bool ready{false};
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EFFECTRESOURCE_HPP
