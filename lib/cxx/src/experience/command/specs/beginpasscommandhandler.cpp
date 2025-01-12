#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/beginpasscommand.hpp>
#include <sway/render/experience/command/specs/beginpasscommandhandler.hpp>

namespace sway::render {
NS_BEGIN(experience)

void BeginPassCommandHandler::handle(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t command) {
  auto *beginPassCommand = static_cast<BeginPassCommandTypedefs::Ptr_t>(command);
}

auto BeginPassCommandHandler::getKey() const -> std::string { return core::ObjectClassName::toStr<BeginPassCommand>(); }

NS_END()  // namespace experience
}  // namespace sway::render
