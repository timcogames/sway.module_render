#ifndef SWAY_RENDER_EXPERIENCE_CLEARCOMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_CLEARCOMMAND_HPP

#include <sway/render/experience/command/command.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class ClearCommand final : public Command {
  DECLARE_CLASS_METADATA(ClearCommand, Command)

public:
#pragma region "Ctors/Dtor"

  ClearCommand()
      : Command(CommandType::Enum::CLEAR) {}

#pragma endregion

#pragma region "Override Command methods"

  MTHD_VIRTUAL_OVERRIDE(void apply()) { std::cout << "ClearCommand" << std::endl; }

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_CLEARCOMMAND_HPP
