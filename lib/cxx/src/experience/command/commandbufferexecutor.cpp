#include <sway/render/experience/command/commandbufferexecutor.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void CommandBufferExecutor::submit(const CommandBufferTypedefs::RefArray_t &refs) {
  for (const auto &ref : refs) {
    CommandType::Enum type;
    while (auto *cmd = ref.get().peek(&type)) {
      switch (type) {
        case CommandType::Enum::BEGIN_PASS:
          handleBeginPass_(cmd);
          break;
        case CommandType::Enum::DRAW:
          handleDraw_(cmd);
          break;
        case CommandType::Enum::END_PASS:
          handleEndPass_(cmd);
          break;
        default:
          throw core::runtime::Exception("Unknown render queue command");
      };

      ref.get().dequeue();
    }
  }
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
