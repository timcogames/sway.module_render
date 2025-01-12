#ifndef SWAY_RENDER_EXPERIENCE_TECHNIQUEMANAGER_HPP
#define SWAY_RENDER_EXPERIENCE_TECHNIQUEMANAGER_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>

namespace sway::render {
NS_BEGIN(experience)

class TechniqueManager {
public:
#pragma region "Registering/Unregistering"

  auto registerTechnique(const std::string &name, TechniqueTypedefs::Builder_t builder) -> bool;

  auto unregister(const std::string &name) -> bool;

#pragma endregion

#pragma region "Getters/Setters"

  auto get(const std::string &name) -> TechniqueTypedefs::BuilderResult_t;

#pragma endregion

private:
  TechniqueTypedefs::RegistryContainer_t techniques_;
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_TECHNIQUEMANAGER_HPP
