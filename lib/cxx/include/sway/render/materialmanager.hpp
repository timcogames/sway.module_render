#ifndef SWAY_RENDER_MATERIALMANAGER_HPP
#define SWAY_RENDER_MATERIALMANAGER_HPP

#include <sway/core.hpp>
#include <sway/render/material.hpp>

#include <map>
#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class MaterialManager {
public:
  MaterialManager();

  ~MaterialManager() = default;

  auto addMaterial(MaterialSharedPtr_t mtrl) -> bool;

  auto getByUid(const std::string &name) -> MaterialSharedPtr_t;

private:
  MaterialSharedPtrMap_t materials_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_MATERIALMANAGER_HPP
