#ifndef SWAY_RENDER_EXPERIENCE_ENDPASSCOMMANDHANDLER_HPP
#define SWAY_RENDER_EXPERIENCE_ENDPASSCOMMANDHANDLER_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/command.hpp>
#include <sway/render/experience/command/commandhandler.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class EndPassCommandHandler final : public CommandHandler {
public:
#pragma region "Overridden CommandHandler methods"

  MTHD_VIRTUAL_OVERRIDE(void handle(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t cmd));

  MTHD_VIRTUAL_OVERRIDE(auto getKey() const -> std::string);

#pragma endregion
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_ENDPASSCOMMANDHANDLER_HPP
