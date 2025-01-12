#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>

namespace sway::render {

RenderQueue::RenderQueue()
    : priority_(core::toBase(core::Priority::Enum::NORMAL)) {}

RenderQueue::RenderQueue(u32_t priority)
    : priority_(priority) {}

RenderQueue::~RenderQueue() {
  for (auto &subqueue : subqueues_) {
    subqueue.clear();
  }
}

void RenderQueue::addSubqueue(const RenderSubqueueSharedPtr_t &subqueue) {
  getSubqueues(subqueue->getGroup()).push_back(subqueue);
}

void RenderQueue::removeSubqueue(const RenderSubqueueSharedPtr_t &subqueue) {
  auto group = subqueue->getGroup();
  auto begin = std::remove(getSubqueues(group).begin(), getSubqueues(group).end(), subqueue);
  getSubqueues(group).erase(begin, getSubqueues(group).end());
}

auto RenderQueue::getSubqueues(RenderSubqueueGroup group) -> RenderSubqueueSharedPtrVec_t & {
  return subqueues_[core::toBase(group)];
}

}  // namespace sway::render
