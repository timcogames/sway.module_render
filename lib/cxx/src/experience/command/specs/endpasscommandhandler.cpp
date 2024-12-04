#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/endpasscommand.hpp>
#include <sway/render/experience/command/specs/endpasscommandhandler.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void EndPassCommandHandler::handle(CommandTypedefs::Ptr_t cmd) { std::cout << "Handling END_PASS" << std::endl; }

auto EndPassCommandHandler::getKey() const -> std::string {
  return core::foundation::ObjectClassname::toStr<EndPassCommand>();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
