#ifndef SWAY_RENDER_EXPERIENCE_TECHNIQUE_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_TECHNIQUE_TYPEDEFS_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Technique;
namespace TechniqueTypedefs {
using Ptr_t = Technique *;
using UniquePtr_t = std::unique_ptr<Technique>;
using Container_t = std::map<u32_t, UniquePtr_t>;
using Builder_t = std::function<void(Technique &, bool)>;
using RegistryContainer_t = std::map<std::string, Builder_t>;
}  // namespace TechniqueTypedefs

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_TECHNIQUE_TYPEDEFS_HPP
