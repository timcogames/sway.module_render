#ifndef SWAY_RENDER_EXPERIENCE_ENDPASSCOMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_ENDPASSCOMMAND_HPP

#include <sway/render/experience/command/command.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class EndPassCommand final : public Command {
  DECLARE_CLASS_METADATA(EndPassCommand, Command)

public:
#pragma region "Ctors/Dtor"

  EndPassCommand()
      : Command(CommandType::Enum::END_PASS) {}

#pragma endregion

#pragma region "Override Command methods"

  MTHD_VIRTUAL_OVERRIDE(void apply()) { std::cout << "EndPassCommand" << std::endl; }

#pragma endregion
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_ENDPASSCOMMAND_HPP
