#ifndef SWAY_RENDER_EXPERIENCE_COMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_COMMAND_HPP

#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandtypes.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class Command {
  DECLARE_SUPERCLASS()

public:
#pragma region "Ctors/Dtor"

  Command(CommandType::Enum type)
      : type_(type)
      , data_(nullptr) {}

  DTOR_VIRTUAL(Command) noexcept {}

#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(void apply());

#pragma endregion

#pragma region "Getters/Setters"

  [[nodiscard]] auto type() const -> CommandType::Enum { return type_; }

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
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMAND_HPP
