#ifndef SWAY_RENDER_MTRL_MATERIALMANAGER_HPP
#define SWAY_RENDER_MTRL_MATERIALMANAGER_HPP

#include <sway/core.hpp>
#include <sway/render/mtrl/_typedefs.hpp>
#include <sway/render/mtrl/material.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class MaterialManager {
public:
#pragma region "Ctors/Dtor"

  MaterialManager() = default;

  DTOR_DEFAULT(MaterialManager);

#pragma endregion

#pragma region "Adding/Updating/Removing"

  auto addMaterial(MaterialTypedefs::SharedPtr_t mtrl) -> bool;

#pragma endregion

#pragma region "Getters/Setters"

  auto getByUid(const std::string &name) -> MaterialTypedefs::SharedPtr_t;

#pragma endregion

private:
  MaterialTypedefs::Container_t materials_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_MTRL_MATERIALMANAGER_HPP
