#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/drawcommand.hpp>
#include <sway/render/experience/command/specs/drawcommandhandler.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void DrawCommandHandler::handle(CommandTypedefs::Ptr_t cmd) { std::cout << "Handling DRAW" << std::endl; }

auto DrawCommandHandler::getKey() const -> std::string {
  return core::foundation::ObjectClassname::toStr<DrawCommand>();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
