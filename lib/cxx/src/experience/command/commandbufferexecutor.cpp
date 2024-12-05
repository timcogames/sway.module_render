#include <sway/render/experience/command/commandbufferexecutor.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void CommandBufferExecutor::registerHandler(CommandHandlerTypedefs::UniquePtr_t &&handler) {
  handlers_.emplace(handler->getKey(), std::move(handler));
}

void CommandBufferExecutor::submit(OperationContext *ctx, const CommandBufferTypedefs::RefArray_t &refs) {
  for (const auto &ref : refs) {
    CommandType::Enum type;
    while (auto *cmd = ref.get().peek(&type)) {
      run_(ctx, cmd);
      ref.get().dequeue();
    }
  }
}

void CommandBufferExecutor::run_(OperationContext *ctx, CommandTypedefs::Ptr_t cmd) {
  for (const auto &[key, handler] : handlers_) {
    if (key == cmd->getClassname()) {
      handler->handle(ctx, cmd);
    }
  }
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
