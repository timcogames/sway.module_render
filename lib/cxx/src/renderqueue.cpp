#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

RenderQueue::RenderQueue()
    : priority_(core::detail::toBase(core::intrusive::Priority::NORMAL)) {}

RenderQueue::RenderQueue(u32_t priority)
    : priority_(priority) {}

RenderQueue::~RenderQueue() {
  for (auto &subqueue : subqueues_) {
    subqueue.clear();
  }
}

void RenderQueue::addSubqueue(const RenderSubqueue::SharedPtr_t &subqueue) {
  getSubqueues(subqueue->getGroup()).push_back(subqueue);
}

void RenderQueue::removeSubqueue(const RenderSubqueue::SharedPtr_t &subqueue) {
  auto group = subqueue->getGroup();
  auto begin = std::remove(getSubqueues(group).begin(), getSubqueues(group).end(), subqueue);
  getSubqueues(group).erase(begin, getSubqueues(group).end());
}

auto RenderQueue::getSubqueues(RenderSubqueueGroup group) -> RenderSubqueueRefVec_t & {
  return subqueues_[core::detail::toBase(group)];
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
