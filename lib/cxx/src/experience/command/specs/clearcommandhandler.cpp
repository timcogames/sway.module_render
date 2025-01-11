#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/clearcommand.hpp>
#include <sway/render/experience/command/specs/clearcommandhandler.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/rendermodule.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void ClearCommandHandler::handle(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t cmd) {
  auto *concreteCmd = static_cast<ClearCommandTypedefs::Ptr_t>(cmd);

  context->viewport->setClearColor(concreteCmd->getColor());
  context->viewport->clear(concreteCmd->getFlags());
}

auto ClearCommandHandler::getKey() const -> std::string { return core::ObjectClassName::toStr<ClearCommand>(); }

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
