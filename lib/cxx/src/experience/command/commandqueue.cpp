#include <sway/render/experience/command/commandqueue.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

auto CommandQueue::createBuffer(const CommandBufferDescriptor &desc) -> CommandBufferTypedefs::OptionalRef_t {
  auto &subqueue = getSubqueue(desc.group);
  subqueue.push_back(std::make_unique<CommandBuffer>(desc));
  return *subqueue.back();
}

void CommandQueue::add(CommandBufferTypedefs::Ptr_t buf) {
  getSubqueue(buf->getGroup()).push_back(std::unique_ptr<CommandBuffer>(buf));
}

void CommandQueue::remove(const CommandBufferTypedefs::UniquePtr_t &buf) {
  auto &subqueue = getSubqueue(buf->getGroup());
  auto iter = std::remove(subqueue.begin(), subqueue.end(), std::move(buf));
  subqueue.erase(iter, subqueue.end());
}

void CommandQueue::process(u32_t idx) {
  CommandBufferTypedefs::RefArray_t refs;
  for (auto &ptr : getSubqueue(idx)) {
    refs.emplace_back(*ptr);
  }

  executor_.submit(refs);
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
