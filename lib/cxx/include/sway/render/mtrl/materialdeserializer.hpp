#ifndef SWAY_RENDER_MTRL_MATERIALDESERIALIZER_HPP
#define SWAY_RENDER_MTRL_MATERIALDESERIALIZER_HPP

#include <sway/core.hpp>
#include <sway/render/mtrl/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

#include <nlohmann/json.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class MaterialDeserializer {
public:
#pragma region "Static methods"

  static auto deserialize(const nlohmann::json &obj) -> MaterialTypedefs::UniquePtr_t {
    auto mtrl = std::make_unique<Material>("name", nullptr, nullptr);
    const auto techniques = obj["techniques"];
    if (!techniques.is_array()) {
      return nullptr;
    }

    for (const auto &tech : techniques.get<std::vector<nlohmann::json::object_t>>()) {
    }

    return std::move(mtrl);
  }

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_MTRL_MATERIALDESERIALIZER_HPP
