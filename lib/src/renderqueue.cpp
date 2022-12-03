#include <sway/graphics/renderqueue.hpp>
#include <sway/graphics/rendersubqueue.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderQueue::RenderQueue()
    : priority_(core::intrusive::kPriority_Normal) {}

RenderQueue::RenderQueue(u32_t priority)
    : priority_(priority) {}

RenderQueue::~RenderQueue() {
  for (auto &subqueue : subqueues_) {
    subqueue.clear();
  }
}

void RenderQueue::addSubqueue(const RenderSubqueueRef_t &subqueue) {
  getSubqueues(subqueue->getGroup()).push_back(subqueue);
}

void RenderQueue::removeSubqueue(const RenderSubqueueRef_t &subqueue) {
  auto items = getSubqueues(subqueue->getGroup());
  getSubqueues(subqueue->getGroup()).erase(std::remove(items.begin(), items.end(), subqueue), items.end());
}

auto RenderQueue::getSubqueues(RenderSubqueueGroup_t group) -> RenderSubqueueRefVec_t & {
  return subqueues_[core::detail::toUnderlying(group)];
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
