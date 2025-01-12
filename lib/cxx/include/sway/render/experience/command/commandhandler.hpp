#ifndef SWAY_RENDER_EXPERIENCE_COMMANDHANDLER_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDHANDLER_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/_typedefs.hpp>
#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/rendercontext.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class CommandHandler {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  DTOR_VIRTUAL(CommandHandler) noexcept {}

  /** @} */
#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(void handle(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t cmd));

  PURE_VIRTUAL(auto getKey() const -> std::string);

#pragma endregion
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDHANDLER_HPP
