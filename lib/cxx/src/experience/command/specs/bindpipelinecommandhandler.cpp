#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/bindpipelinecommand.hpp>
#include <sway/render/experience/command/specs/bindpipelinecommandhandler.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void BindPipelineCommandHandler::handle(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t cmd) {
  auto *concreteCommand = static_cast<BindPipelineCommandTypedefs::Ptr_t>(cmd);

  std::cout << "Handling BIND_PIPELINE" << std::endl;
}

auto BindPipelineCommandHandler::getKey() const -> std::string {
  return core::foundation::ObjectClassname::toStr<BindPipelineCommand>();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
