#include <sway/graphics/rendersubsystem.h>
#include <sway/graphics/rendersubqueuegroups.h>
#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/renderqueue.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderSubsystem::RenderSubsystem(core::foundation::Context * context) : core::foundation::Object(context) {
	_caps = new gapi::Capabilities();
	
	auto version = _caps->getGLVersion();
	std::cout << boost::str(boost::format("%1%.%2%") % version.getMajor() % version.getMinor()) << std::endl;
}

RenderSubsystem::~RenderSubsystem() {
	SAFE_DELETE(_caps);
	_queues.clear();
}

RenderQueueRef_t RenderSubsystem::createQueue(u32_t priority) {
	_queues.push_back(boost::make_shared<RenderQueue>(priority));
	return _queues.back();
}

RenderQueueRef_t RenderSubsystem::getQueueByIdx(u32_t index) {
	return _queues[index];
}

RenderQueueRefVector_t RenderSubsystem::getQueues() {
	return _queues;
}

void RenderSubsystem::sortQueues() {
	if (_queues.size() >= 2)
		std::sort(_queues.begin(), _queues.end(), RenderQueue::PriorityInDescendingOrder());
}

void RenderSubsystem::render() {
	for (u32_t i = 0; i < _queues.size(); ++i) {
		_renderSubqueues(_queues[i], kRenderSubqueueGroup_Opaque);
		_renderSubqueues(_queues[i], kRenderSubqueueGroup_Transparent);
	}
}

void RenderSubsystem::_renderSubqueues(RenderQueueRef_t queue, u32_t group) {
	const RenderSubqueueRefVec_t & subqueues = queue->getSubqueueGroupByIdx(group);

	if (subqueues.size() > 0) {
		BOOST_FOREACH (const RenderSubqueueRef_t & subqueue, subqueues)
			subqueue->render();
	}
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
