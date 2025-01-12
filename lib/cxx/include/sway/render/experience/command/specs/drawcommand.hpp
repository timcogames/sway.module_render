#ifndef SWAY_RENDER_EXPERIENCE_DRAWCOMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_DRAWCOMMAND_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/command.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class DrawCommand final : public Command {
  DECLARE_CLASS_METADATA(DrawCommand, Command)

public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  DrawCommand(gapi::TopologyType::Enum topology)
      : Command(CommandType::Enum::DRAW)
      , topology_(topology) {}

  /** @} */
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
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_DRAWCOMMAND_HPP
