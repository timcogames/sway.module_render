#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/bindpipelinecommand.hpp>
#include <sway/render/experience/command/specs/bindpipelinecommandhandler.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void BindPipelineCommandHandler::handle(CommandTypedefs::Ptr_t cmd) {
  std::cout << "BindPipelineCommandHandler" << std::endl;
}

auto BindPipelineCommandHandler::getKey() const -> std::string {
  return core::foundation::ObjectClassname::toStr<BindPipelineCommand>();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
