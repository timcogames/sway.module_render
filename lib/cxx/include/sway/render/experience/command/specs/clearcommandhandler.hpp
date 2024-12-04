#ifndef SWAY_RENDER_EXPERIENCE_CLEARCOMMANDHANDLER_HPP
#define SWAY_RENDER_EXPERIENCE_CLEARCOMMANDHANDLER_HPP

#include <sway/render/experience/command/command.hpp>
#include <sway/render/experience/command/commandhandler.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class ClearCommandHandler final : public CommandHandler {
public:
#pragma region "Ctors/Dtor"

  ClearCommandHandler(gapi::ViewportPtr_t viewport)
      : viewport_(viewport) {}

#pragma endregion

#pragma region "Override CommandHandler methods"

  MTHD_VIRTUAL_OVERRIDE(void handle(CommandTypedefs::Ptr_t cmd));

  MTHD_VIRTUAL_OVERRIDE(auto getKey() const -> std::string);

#pragma endregion

private:
  gapi::ViewportPtr_t viewport_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_CLEARCOMMANDHANDLER_HPP
