#ifndef SWAY_RENDER_EFFECT_TYPEDEFS_HPP
#define SWAY_RENDER_EFFECT_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {

class Effect;
namespace EffectTypedefs {
using Ptr_t = Effect *;
using SharedPtr_t = std::shared_ptr<Effect>;
}  // namespace EffectTypedefs

namespace EffectMacroTypedefs {
using Container_t = std::vector<std::pair<std::string, std::string>>;
}  // namespace EffectMacroTypedefs

struct EffectResourceImmutable;
namespace EffectResourceImmutableTypedefs {
using SharedPtr_t = std::shared_ptr<EffectResourceImmutable>;
}  // namespace EffectResourceImmutableTypedefs

}  // namespace sway::render

#endif  // SWAY_RENDER_EFFECT_TYPEDEFS_HPP
