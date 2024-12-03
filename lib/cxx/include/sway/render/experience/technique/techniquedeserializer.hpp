#ifndef SWAY_RENDER_EXPERIENCE_TECHNIQUEDESERIALIZER_HPP
#define SWAY_RENDER_EXPERIENCE_TECHNIQUEDESERIALIZER_HPP

#include <sway/core.hpp>
#include <sway/render/experience/pass/passdeserializer.hpp>
#include <sway/render/experience/pass/specs/graphicspass.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

#include <nlohmann/json.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class TechniqueDeserializer {
public:
#pragma region "Static methods"

  static auto deserialize(const nlohmann::json &obj) -> TechniqueTypedefs::UniquePtr_t {
    auto tech = std::make_unique<Technique>(obj["name"].get<std::string>());
    auto impl = obj["impl"].get<nlohmann::json::object_t>();
    auto passes = impl["passes"];
    if (!passes.is_array()) {
      return nullptr;
    }

    for (auto &pass : passes.get<std::vector<nlohmann::json::object_t>>()) {
      tech->getPasses()->getOrCreate<GraphicsPass>(PassDeserializer::deserialize<PassDescriptor>(pass));
    }

    return std::move(tech);
  }

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_TECHNIQUEDESERIALIZER_HPP
