#include <sway/graphics/renderqueue.h>
#include <sway/graphics/rendersubqueue.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderQueue::RenderQueue(u32_t priority)
	: _priority(priority) {
	// Empty
}

RenderQueue::~RenderQueue() {
	for (u32_t i = 0; i < RENDER_SUBQUEUE_GROUP_COUNT; ++i)
		_subqueues[i].clear();
}

void RenderQueue::addSubqueue(const RenderSubqueueRef_t & subqueue) {
	u32_t groupIdx = subqueue->getGroupIdx();
	_subqueues[groupIdx].push_back(subqueue);
}

void RenderQueue::removeSubqueue(const RenderSubqueueRef_t & subqueue) {
	u32_t groupIdx = subqueue->getGroupIdx();
	_subqueues[groupIdx].erase(std::remove(_subqueues[groupIdx].begin(), _subqueues[groupIdx].end(), subqueue), _subqueues[groupIdx].end());
}

RenderSubqueueRefVec_t & RenderQueue::getSubqueueGroupByIdx(u32_t groupIdx) {
	if (groupIdx > RENDER_SUBQUEUE_GROUP_COUNT)
		throw ArgumentException("groupIdx");

	return _subqueues[groupIdx];
}

void RenderQueue::setPriority(u32_t priority) {
	_priority = priority;
}

u32_t RenderQueue::getPriority() const {
	return _priority;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
