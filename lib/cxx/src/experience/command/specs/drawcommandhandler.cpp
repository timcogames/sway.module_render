#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/drawcommand.hpp>
#include <sway/render/experience/command/specs/drawcommandhandler.hpp>

namespace sway::render {
NS_BEGIN(experience)

void DrawCommandHandler::handle(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t cmd) {
  auto *concreteCmd = static_cast<DrawCommandTypedefs::Ptr_t>(cmd);

#ifdef RENDER_USE_GMOCK

  gapi::BufferSet bufset;
  context->drawCall->execute(concreteCmd->getTopology(), bufset, core::ValueDataType::Enum::UINT);

#endif
}

auto DrawCommandHandler::getKey() const -> std::string { return core::ObjectClassName::toStr<DrawCommand>(); }

NS_END()  // namespace experience
}  // namespace sway::render
