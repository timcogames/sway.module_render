#ifndef SWAY_RENDER_EXPERIENCE_TECHNIQUE_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_TECHNIQUE_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct TechniqueMetadata {};

class Technique;
namespace TechniqueTypedefs {
using Ptr_t = Technique *;
using UniquePtr_t = std::unique_ptr<Technique>;
using SharedPtr_t = std::shared_ptr<Technique>;
using Builder_t = std::function<void(Technique &, const TechniqueMetadata &)>;
using BuilderResult_t = std::optional<Builder_t>;
using RegistryContainer_t = std::unordered_map<std::string, Builder_t>;
}  // namespace TechniqueTypedefs

class TechniqueManager;
namespace TechniqueManagerTypedefs {
using Ptr_t = TechniqueManager *;
using UniquePtr_t = std::unique_ptr<TechniqueManager>;
}  // namespace TechniqueManagerTypedefs

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_TECHNIQUE_TYPEDEFS_HPP
