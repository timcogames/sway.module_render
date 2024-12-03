#ifndef SWAY_RENDER_EXPERIENCE_PASSDESERIALIZER_HPP
#define SWAY_RENDER_EXPERIENCE_PASSDESERIALIZER_HPP

#include <sway/core.hpp>
#include <sway/render/experience/pass/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

#include <nlohmann/json.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class PassDeserializer {
public:
#pragma region "Static methods"

  template <class TARGET>
  static auto deserialize_depricated(const nlohmann::json &obj) -> std::unique_ptr<TARGET> {
    auto id = obj["id"].get<u32_t>();
    auto shader = obj["shader"].get<nlohmann::json::object_t>();

    auto pass = std::make_unique<TARGET>((struct PassDescriptor){.format = 0});
    return std::move(pass);
  }

  template <typename DESC>
  static auto deserialize(const nlohmann::json &obj) -> DESC {
    auto id = obj["id"].get<u32_t>();
    auto shader = obj["shader"].get<nlohmann::json::object_t>();

    return {.format = 0};
  }

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PASSDESERIALIZER_HPP
