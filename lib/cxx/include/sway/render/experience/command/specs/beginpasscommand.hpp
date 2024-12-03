#ifndef SWAY_RENDER_EXPERIENCE_BEGINPASSCOMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_BEGINPASSCOMMAND_HPP

#include <sway/render/experience/command/command.hpp>
#include <sway/render/experience/pass/pass.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class BeginPassCommand final : public Command {
  DECLARE_CLASS_METADATA(BeginPassCommand, Command)

public:
#pragma region "Ctors/Dtor"

  BeginPassCommand(Pass const &pass)
      : Command(CommandType::Enum::BEGIN_PASS)
      , pass_(pass) {}

#pragma endregion

#pragma region "Override Command methods"

  MTHD_VIRTUAL_OVERRIDE(void apply()) { std::cout << "BeginPassCommand" << std::endl; }

#pragma endregion

private:
  Pass const &pass_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_BEGINPASSCOMMAND_HPP
