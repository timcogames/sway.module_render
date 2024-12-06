
#include <sway/render/experience/technique/techniquemanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

auto TechniqueManager::registerTechnique(const std::string &name, TechniqueTypedefs::Builder_t builder) -> bool {
  auto const [iter, success] = techniques_.try_emplace(name, std::move(builder));
  return success;
}

auto TechniqueManager::unregister(const std::string &name) -> bool { return techniques_.erase(name) == 1; }

auto TechniqueManager::get(const std::string &name) -> TechniqueTypedefs::BuilderResult_t {
  if (auto iter = techniques_.find(name); iter != techniques_.end()) {
    return iter->second;
  }

  std::cout << "Undefined default technique for " << name << std::endl;
  return std::nullopt;
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
