#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/clearcommand.hpp>
#include <sway/render/experience/command/specs/clearcommandhandler.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void ClearCommandHandler::handle(CommandTypedefs::Ptr_t cmd) {
  auto concreteCommand = static_cast<ClearCommand *>(cmd);
  viewport_->setClearColor(concreteCommand->getColor());
  viewport_->clear(concreteCommand->getFlags());

  std::cout << "Handling CLEAR" << std::endl;
}

auto ClearCommandHandler::getKey() const -> std::string {
  return core::foundation::ObjectClassname::toStr<ClearCommand>();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
