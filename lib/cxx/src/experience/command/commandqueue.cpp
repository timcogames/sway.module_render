#include <sway/render/experience/command/commandqueue.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

void CommandQueue::add(CommandBufferTypedefs::Ptr_t buf) { buffers_.push_back(std::unique_ptr<CommandBuffer>(buf)); }

void CommandQueue::remove(const CommandBufferTypedefs::UniquePtr_t &buf) {
  auto iter = std::remove(buffers_.begin(), buffers_.end(), std::move(buf));
  buffers_.erase(iter, buffers_.end());
}

void CommandQueue::process(OperationContext *ctx) {
  CommandBufferTypedefs::RefArray_t refs;
  for (auto &ptr : buffers_) {
    refs.emplace_back(*ptr);
  }

  executor_.submit(ctx, refs);
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
