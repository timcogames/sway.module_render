#ifndef SWAY_RENDER_EXPERIENCE_COMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_COMMAND_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandtypes.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class Command {
  DECLARE_SUPERCLASS()

public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Command(CommandType::Enum type)
      : type_(type)
      , data_(nullptr) {}

  DTOR_VIRTUAL(Command) noexcept {}

  /** @} */
#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(void apply());

#pragma endregion

#pragma region "Getters/Setters"

  [[nodiscard]] auto getType() const -> CommandType::Enum { return type_; }

#pragma endregion

private:
  CommandType::Enum type_;
  void *data_;
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_COMMAND_HPP
