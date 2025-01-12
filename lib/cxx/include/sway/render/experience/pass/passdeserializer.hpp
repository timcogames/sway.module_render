#ifndef SWAY_RENDER_EXPERIENCE_PASSDESERIALIZER_HPP
#define SWAY_RENDER_EXPERIENCE_PASSDESERIALIZER_HPP

#include <sway/core.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/pass/_typedefs.hpp>

#include <nlohmann/json.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup pass
 * @{
 */

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

/**
 * end of pass group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_PASSDESERIALIZER_HPP
