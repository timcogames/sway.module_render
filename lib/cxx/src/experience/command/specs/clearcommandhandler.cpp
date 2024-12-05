#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/clearcommand.hpp>
#include <sway/render/experience/command/specs/clearcommandhandler.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/rendermodule.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void ClearCommandHandler::handle(OperationContext *ctx, CommandTypedefs::Ptr_t cmd) {
  auto *concreteCommand = static_cast<ClearCommandTypedefs::Ptr_t>(cmd);

  ctx->viewport->setClearColor(concreteCommand->getColor());
  ctx->viewport->clear(concreteCommand->getFlags());

  std::cout << "Handling CLEAR" << std::endl;
}

auto ClearCommandHandler::getKey() const -> std::string {
  return core::foundation::ObjectClassname::toStr<ClearCommand>();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
