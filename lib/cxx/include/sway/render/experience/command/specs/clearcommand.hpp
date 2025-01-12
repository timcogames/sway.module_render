#ifndef SWAY_RENDER_EXPERIENCE_CLEARCOMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_CLEARCOMMAND_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/command.hpp>
#include <sway/render/experience/command/commandtypes.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class ClearCommand final : public Command {
  DECLARE_CLASS_METADATA(ClearCommand, Command)

public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  ClearCommand(const math::col4f_t &color, gapi::ClearFlag flags)
      : Command(CommandType::Enum::CLEAR)
      , color_(color)
      , flags_(flags) {}

  /** @} */
#pragma endregion

#pragma region "Overridden Command methods"

  MTHD_VIRTUAL_OVERRIDE(void apply()) { std::cout << "ClearCommand" << std::endl; }

#pragma endregion

#pragma region "Getters/Setters"

  [[nodiscard]] auto getColor() const -> const math::col4f_t & { return color_; }

  [[nodiscard]] auto getFlags() const -> gapi::ClearFlag { return flags_; }

#pragma endregion

private:
  math::col4f_t color_;
  gapi::ClearFlag flags_;
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_CLEARCOMMAND_HPP
