#ifndef SWAY_RENDER_EXPERIENCE_DRAWCOMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_DRAWCOMMAND_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/command.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class DrawCommand final : public Command {
  DECLARE_CLASS_METADATA(DrawCommand, Command)

public:
#pragma region "Ctors/Dtor"

  DrawCommand(gapi::TopologyType::Enum topology)
      : Command(CommandType::Enum::DRAW)
      , topology_(topology) {}

#pragma endregion

#pragma region "Overridden Command methods"

  MTHD_VIRTUAL_OVERRIDE(void apply()) { std::cout << "DrawCommand" << std::endl; }

#pragma endregion

#pragma region "Getters/Setters"

  [[nodiscard]] auto getTopology() const -> gapi::TopologyType::Enum { return topology_; }

#pragma endregion

private:
  gapi::TopologyType::Enum topology_;
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_DRAWCOMMAND_HPP
