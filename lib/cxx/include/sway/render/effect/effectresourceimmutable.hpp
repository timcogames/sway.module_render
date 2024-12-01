#ifndef SWAY_RENDER_EFFECTRESOURCEIMMUTABLE_HPP
#define SWAY_RENDER_EFFECTRESOURCEIMMUTABLE_HPP

#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/effect/effectresource.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

struct EffectResourceImmutable final {
  EffectResource resource;
  EffectMacroTypedefs::Container_t macros;
  u64_t timestamp;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EFFECTRESOURCEIMMUTABLE_HPP
