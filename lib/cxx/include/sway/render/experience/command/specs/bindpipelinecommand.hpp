#ifndef SWAY_RENDER_EXPERIENCE_BINDPIPELINECOMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_BINDPIPELINECOMMAND_HPP

#include <sway/render/experience/command/command.hpp>
#include <sway/render/experience/pipeline/pipeline.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class BindPipelineCommand final : public Command {
  DECLARE_CLASS_METADATA(BindPipelineCommand, Command)

public:
#pragma region "Ctors/Dtor"

  BindPipelineCommand(Pipeline const &pipe)
      : Command(CommandType::Enum::BIND_PIPELINE)
      , pipeline_(pipe) {}

#pragma endregion

#pragma region "Override Command methods"

  MTHD_VIRTUAL_OVERRIDE(void apply()) { std::cout << "BindPipelineCommand" << std::endl; }

#pragma endregion

private:
  Pipeline const &pipeline_;
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_BINDPIPELINECOMMAND_HPP
