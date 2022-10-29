#include <sway/graphics/renderqueue.hpp>
#include <sway/graphics/rendersubqueue.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderQueue::RenderQueue()
    : _priority(core::intrusive::kPriority_Normal) {
  // Empty
}

RenderQueue::RenderQueue(u32_t priority)
    : _priority(priority) {
  // Empty
}

RenderQueue::~RenderQueue() {
  for (u32_t i = 0; i < RENDER_SUBQUEUE_GROUP_COUNT; ++i) {
    _subqueues[i].clear();
  }
}

void RenderQueue::addSubqueue(const RenderSubqueueRef_t &subqueue) {
  getSubqueues(subqueue->getGroup()).push_back(subqueue);
}

void RenderQueue::removeSubqueue(const RenderSubqueueRef_t &subqueue) {
  auto items = getSubqueues(subqueue->getGroup());
  getSubqueues(subqueue->getGroup()).erase(std::remove(items.begin(), items.end(), subqueue), items.end());
}

RenderSubqueueRefVec_t &RenderQueue::getSubqueues(RenderSubqueueGroup_t group) {
  return _subqueues[core::detail::toUnderlying(group)];
}

void RenderQueue::setPriority(u32_t priority) { _priority = priority; }

u32_t RenderQueue::getPriority() const { return _priority; }

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
