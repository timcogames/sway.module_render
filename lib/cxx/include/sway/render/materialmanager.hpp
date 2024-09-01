#ifndef SWAY_RENDER_MATERIALMANAGER_HPP
#define SWAY_RENDER_MATERIALMANAGER_HPP

#include <sway/core.hpp>
#include <sway/render/material.hpp>

#include <map>
#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class MaterialManager {
public:
  MaterialManager();

  ~MaterialManager() = default;

  auto addMaterial(MaterialSharedPtr_t mtrl) -> bool;

  auto getByUid(const std::string &name) -> MaterialSharedPtr_t;

private:
  MaterialSharedPtrMap_t materials_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_MATERIALMANAGER_HPP
