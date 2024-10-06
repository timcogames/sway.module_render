#include <sway/render/materialmanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

MaterialManager::MaterialManager() {}

auto MaterialManager::addMaterial(MaterialSharedPtr_t mtrl) -> bool {
  materials_.insert(MaterialSharedPtrMap_t::value_type(mtrl->getUid().value(), mtrl));
  return true;
}

auto MaterialManager::getByUid(const std::string &name) -> MaterialSharedPtr_t {
  auto iter = materials_.find(name);
  if (iter != materials_.end()) {
    return iter->second;
  }

  return nullptr;
}

NS_END()  // namespace render
NS_END()  // namespace sway
