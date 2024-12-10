#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/specs/drawcommand.hpp>
#include <sway/render/experience/command/specs/drawcommandhandler.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void DrawCommandHandler::handle(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t cmd) {
  auto *concreteCmd = static_cast<DrawCommandTypedefs::Ptr_t>(cmd);

#ifdef RENDER_USE_GMOCK

  gapi::BufferSet bufset;
  context->drawCall->execute(concreteCmd->getTopology(), bufset, core::ValueDataType::Enum::UINT);

#endif
}

auto DrawCommandHandler::getKey() const -> std::string {
  return core::foundation::ObjectClassname::toStr<DrawCommand>();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
