#include <sway/render/experience/command/commandbuffer.hpp>
#include <sway/render/experience/command/commandqueue.hpp>

namespace sway::render {
NS_BEGIN(experience)

auto CommandBuffer::create(CommandQueueTypedefs::UniquePtr_t &owner, const CommandBufferDescriptor &desc)
    -> CommandBufferTypedefs::OptionalRef_t {
  owner->getCommandBuffers().push_back(std::make_unique<CommandBuffer>(desc));
  return *owner->getCommandBuffers().back();
}

void CommandBuffer::enqueue(CommandTypedefs::UniquePtr_t &&cmd) { commands_.push(std::move(cmd)); }

void CommandBuffer::dequeue() {
  if (isEmpty()) {
    return;
  }

  commands_.pop();
}

auto CommandBuffer::peek(CommandType::Enum *type) const -> CommandTypedefs::Ptr_t {
  if (isEmpty()) {
    return nullptr;
  }

  auto *cmd = commands_.front().get();
  *type = cmd->getType();
  return cmd;
}

NS_END()  // namespace experience
}  // namespace sway::render
