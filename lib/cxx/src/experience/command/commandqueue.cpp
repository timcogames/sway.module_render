#include <sway/render/experience/command/commandqueue.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

auto CommandQueue::createBuffer(const CommandBufferDescriptor &desc) -> CommandBufferTypedefs::OptionalRef_t {
  subqueue(desc.group).push_back(std::make_unique<CommandBuffer>(desc));
  return *subqueue(desc.group).back();
}

void CommandQueue::add(CommandBufferTypedefs::Ptr_t buf) {
  subqueue(buf->group()).push_back(std::unique_ptr<CommandBuffer>(buf));
}

void CommandQueue::remove(const CommandBufferTypedefs::UniquePtr_t &buf) {
  auto group = buf->group();
  auto begin = std::remove(subqueue(group).begin(), subqueue(group).end(), std::move(buf));
  subqueue(group).erase(begin, subqueue(group).end());
}

void CommandQueue::process(u32_t idx) {
  CommandBufferTypedefs::RefArray_t refs;
  for (auto &ptr : subqueue(idx)) {
    refs.emplace_back(*ptr);
  }

  executor_.submit(refs);
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
