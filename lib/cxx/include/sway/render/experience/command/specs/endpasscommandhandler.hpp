#ifndef SWAY_RENDER_EXPERIENCE_ENDPASSCOMMANDHANDLER_HPP
#define SWAY_RENDER_EXPERIENCE_ENDPASSCOMMANDHANDLER_HPP

#include <sway/render/experience/command/command.hpp>
#include <sway/render/experience/command/commandhandler.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class EndPassCommandHandler final : public CommandHandler {
public:
#pragma region "Pure virtual methods"

  MTHD_VIRTUAL_OVERRIDE(void handle(CommandTypedefs::Ptr_t cmd));

  MTHD_VIRTUAL_OVERRIDE(auto key() const -> std::string);

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_ENDPASSCOMMANDHANDLER_HPP
