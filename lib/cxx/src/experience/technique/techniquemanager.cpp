
#include <sway/render/experience/technique/techniquemanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

auto TechniqueManager::registerTech(const std::string &name, TechniqueTypedefs::Builder_t builder) -> bool {
  auto const [iter, success] = registers_.try_emplace(name, std::move(builder));
  return success;
}

auto TechniqueManager::unregister(const std::string &name) -> bool { return registers_.erase(name) == 1; }

auto TechniqueManager::get(const std::string &name) -> TechniqueTypedefs::BuilderResult_t {
  if (auto iter = registers_.find(name); iter != registers_.end()) {
    return iter->second;
  }

  std::cout << "Undefined default technique for " << name << std::endl;
  return std::nullopt;
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
