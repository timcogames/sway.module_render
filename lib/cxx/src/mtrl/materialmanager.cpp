#include <sway/render/mtrl/materialmanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

auto MaterialManager::addMaterial(MaterialTypedefs::SharedPtr_t mtrl) -> bool {
  materials_.insert(MaterialTypedefs::Container_t::value_type(mtrl->getUid().value(), mtrl));
  return true;
}

auto MaterialManager::getByUid(const std::string &name) -> MaterialTypedefs::SharedPtr_t {
  auto iter = materials_.find(name);
  if (iter != materials_.end()) {
    return iter->second;
  }

  return nullptr;
}

NS_END()  // namespace render
NS_END()  // namespace sway
