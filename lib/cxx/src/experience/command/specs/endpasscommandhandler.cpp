#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/endpasscommand.hpp>
#include <sway/render/experience/command/specs/endpasscommandhandler.hpp>

namespace sway::render {
NS_BEGIN(experience)

void EndPassCommandHandler::handle(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t cmd) {
  auto *concreteCommand = static_cast<EndPassCommandTypedefs::Ptr_t>(cmd);

  std::cout << "Handling END_PASS" << std::endl;
}

auto EndPassCommandHandler::getKey() const -> std::string { return core::ObjectClassName::toStr<EndPassCommand>(); }

NS_END()  // namespace experience
}  // namespace sway::render
