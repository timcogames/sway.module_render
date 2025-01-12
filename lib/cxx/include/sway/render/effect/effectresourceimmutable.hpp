#ifndef SWAY_RENDER_EFFECTRESOURCEIMMUTABLE_HPP
#define SWAY_RENDER_EFFECTRESOURCEIMMUTABLE_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/effect/effectresource.hpp>

namespace sway::render {

struct EffectResourceImmutable final {
  EffectResource resource;
  EffectMacroTypedefs::Container_t macros;
  u64_t timestamp;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_EFFECTRESOURCEIMMUTABLE_HPP
