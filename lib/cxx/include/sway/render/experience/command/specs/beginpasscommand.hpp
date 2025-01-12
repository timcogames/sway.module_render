#ifndef SWAY_RENDER_EXPERIENCE_BEGINPASSCOMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_BEGINPASSCOMMAND_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/command.hpp>
#include <sway/render/experience/pass/pass.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class BeginPassCommand final : public Command {
  DECLARE_CLASS_METADATA(BeginPassCommand, Command)

public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  BeginPassCommand(Pass const &pass)
      : Command(CommandType::Enum::BEGIN_PASS)
      , pass_(pass) {}

  /** @} */
#pragma endregion

#pragma region "Overridden Command methods"

  MTHD_VIRTUAL_OVERRIDE(void apply()) { std::cout << "BeginPassCommand" << std::endl; }

#pragma endregion

private:
  Pass const &pass_;
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_BEGINPASSCOMMAND_HPP
