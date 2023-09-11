#ifndef SWAY_RENDER_MATERIALMANAGER_HPP
#define SWAY_RENDER_MATERIALMANAGER_HPP

#include <sway/core.hpp>
#include <sway/render/material.hpp>

#include <map>
#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

using MaterialPtr_t = std::shared_ptr<Material>;
using MaterialMap_t = std::map<std::string, MaterialPtr_t>;

class MaterialManager {
public:
  MaterialManager();

  ~MaterialManager() = default;

  auto addMaterial(MaterialPtr_t mtrl) -> bool;

  auto getByUid(const std::string &name) -> MaterialPtr_t;

private:
  MaterialMap_t materials_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_MATERIALMANAGER_HPP
