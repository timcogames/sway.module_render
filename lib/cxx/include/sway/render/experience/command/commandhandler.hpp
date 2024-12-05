#ifndef SWAY_RENDER_EXPERIENCE_COMMANDHANDLER_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDHANDLER_HPP

#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class CommandHandler {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL(CommandHandler) noexcept {}

#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(void handle(OperationContext *ctx, CommandTypedefs::Ptr_t cmd));

  PURE_VIRTUAL(auto getKey() const -> std::string);

#pragma endregion
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDHANDLER_HPP
