#ifndef SWAY_RENDER_EFFECT_TYPEDEFS_HPP
#define SWAY_RENDER_EFFECT_TYPEDEFS_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Effect;
namespace EffectTypedefs {
using Ptr_t = Effect *;
}  // namespace EffectTypedefs

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EFFECT_TYPEDEFS_HPP
