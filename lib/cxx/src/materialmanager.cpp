#include <sway/render/materialmanager.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

MaterialManager::MaterialManager() {}

auto MaterialManager::addMaterial(MaterialPtr_t mtrl) -> bool {
  materials_.insert(MaterialMap_t::value_type(mtrl->getUid().value(), mtrl));
  return true;
}

auto MaterialManager::getByUid(const std::string &name) -> MaterialPtr_t {
  MaterialMap_t::iterator iter = materials_.find(name);
  if (iter != materials_.end()) {
    return iter->second;
  }

  return nullptr;
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
