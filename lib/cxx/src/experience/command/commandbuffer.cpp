#include <sway/render/experience/command/commandbuffer.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void CommandBuffer::enqueue(CommandTypedefs::UniquePtr_t &&cmd) { commands_.push(std::move(cmd)); }

void CommandBuffer::dequeue() {
  if (empty()) {
    return;
  }

  commands_.pop();
}

auto CommandBuffer::peek(CommandType::Enum *type) const -> CommandTypedefs::Ptr_t {
  if (empty()) {
    return nullptr;
  }

  auto *cmd = commands_.front().get();
  *type = cmd->type;
  return cmd;
}

auto CommandBuffer::empty() const -> bool { return commands_.empty(); }

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
