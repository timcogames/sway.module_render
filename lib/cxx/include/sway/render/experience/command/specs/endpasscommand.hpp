#ifndef SWAY_RENDER_EXPERIENCE_ENDPASSCOMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_ENDPASSCOMMAND_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/command.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class EndPassCommand final : public Command {
  DECLARE_CLASS_METADATA(EndPassCommand, Command)

public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  EndPassCommand()
      : Command(CommandType::Enum::END_PASS) {}

  /** @} */
#pragma endregion

#pragma region "Overridden Command methods"

  MTHD_VIRTUAL_OVERRIDE(void apply()) { std::cout << "EndPassCommand" << std::endl; }

#pragma endregion
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_ENDPASSCOMMAND_HPP
