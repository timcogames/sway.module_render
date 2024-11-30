
#include <sway/render/experience/technique/techniquemanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

auto TechniqueManager::registerTech(const std::string &name, TechniqueTypedefs::Builder_t builder) -> bool {
  auto result = registers_.insert({name, builder});
  return result.second;
}

auto TechniqueManager::unregister(const std::string &name) -> bool {
  auto erased = registers_.erase(name);
  return (erased == 1);
}

auto TechniqueManager::get(const std::string &name) -> TechniqueTypedefs::BuilderResult_t {
  auto iter = registers_.find(name);
  if (iter != registers_.end()) {
    return iter->second;
  }

  std::cout << "Undefined default technique for " << name << std::endl;
  return std::nullopt;
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
