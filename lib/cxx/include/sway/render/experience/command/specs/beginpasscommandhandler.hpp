#ifndef SWAY_RENDER_EXPERIENCE_BEGINPASSCOMMANDHANDLER_HPP
#define SWAY_RENDER_EXPERIENCE_BEGINPASSCOMMANDHANDLER_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/command/command.hpp>
#include <sway/render/experience/command/commandhandler.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

class BeginPassCommandHandler final : public CommandHandler {
public:
#pragma region "Overridden CommandHandler methods"

  MTHD_VIRTUAL_OVERRIDE(void handle(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t cmd));

  MTHD_VIRTUAL_OVERRIDE(auto getKey() const -> std::string);

#pragma endregion
};

/** @} */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_BEGINPASSCOMMANDHANDLER_HPP
