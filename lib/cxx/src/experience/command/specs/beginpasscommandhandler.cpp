#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/beginpasscommand.hpp>
#include <sway/render/experience/command/specs/beginpasscommandhandler.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void BeginPassCommandHandler::handle(OperationContext *ctx, CommandTypedefs::Ptr_t cmd) {
  auto *concreteCommand = static_cast<BeginPassCommandTypedefs::Ptr_t>(cmd);

  std::cout << "Handling BEGIN_PASS" << std::endl;
}

auto BeginPassCommandHandler::getKey() const -> std::string {
  return core::foundation::ObjectClassname::toStr<BeginPassCommand>();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
