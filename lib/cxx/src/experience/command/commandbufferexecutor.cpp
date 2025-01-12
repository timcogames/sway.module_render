#include <sway/render/experience/command/commandbufferexecutor.hpp>

namespace sway::render {
NS_BEGIN(experience)

void CommandBufferExecutor::registerHandler(CommandHandlerTypedefs::UniquePtr_t &&handler) {
  handlers_.emplace(handler->getKey(), std::move(handler));
}

void CommandBufferExecutor::submit(
    DeviceContextTypedefs::Ptr_t context, const CommandBufferTypedefs::RefArray_t &refs) {
  for (const auto &ref : refs) {
    CommandType::Enum type;
    while (auto *cmd = ref.get().peek(&type)) {
      run_(context, cmd);
      ref.get().dequeue();
    }
  }
}

void CommandBufferExecutor::run_(DeviceContextTypedefs::Ptr_t context, CommandTypedefs::Ptr_t cmd) {
  for (const auto &[key, handler] : handlers_) {
    if (key == cmd->getClassname()) {
      handler->handle(context, cmd);
    }
  }
}

NS_END()  // namespace experience
}  // namespace sway::render
