#include <sway/graphics/renderqueue.h>
#include <sway/graphics/renderqueuepriorities.h>
#include <sway/graphics/rendersubqueue.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderQueue::RenderQueue()
	: _priority(kRenderQueuePriority_Normal) {
	// Empty
}

RenderQueue::~RenderQueue() {
	for (u32_t i = 0; i < RENDER_SUBQUEUE_GROUP_COUNT; ++i)
		_subqueues[i].clear();
}

void RenderQueue::addSubqueue(const RenderSubqueueRef_t & subqueue) {
	u32_t groupIndex = subqueue->getGroupIdx();
	if (groupIndex > RENDER_SUBQUEUE_GROUP_COUNT)
		std::invalid_argument("groupIndex");

	_subqueues[groupIndex].push_back(subqueue);
}

void RenderQueue::removeSubqueue(const RenderSubqueueRef_t & subqueue) {
	u32_t groupIndex = subqueue->getGroupIdx();
	if (groupIndex > RENDER_SUBQUEUE_GROUP_COUNT)
		std::invalid_argument("groupIndex");

	_subqueues[groupIndex].erase(std::remove(_subqueues[groupIndex].begin(), _subqueues[groupIndex].end(), subqueue), _subqueues[groupIndex].end());
}

RenderSubqueueRefVector_t & RenderQueue::getSubqueueGroupByIdx(u32_t groupIdx) {
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
