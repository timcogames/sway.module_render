#include <sway/render/mtrl/materialmanager.hpp>

namespace sway::render {

auto MaterialManager::addMaterial(MaterialTypedefs::SharedPtr_t mtrl) -> bool {
  auto [iter, inserted] = materials_.emplace(mtrl->getUniqueId().value(), mtrl);
  return inserted;
}

auto MaterialManager::getByUid(const std::string &name) -> MaterialTypedefs::SharedPtr_t {
  auto iter = materials_.find(name);
  if (iter != materials_.end()) {
    return iter->second;
  }

  return nullptr;
}

}  // namespace sway::render
