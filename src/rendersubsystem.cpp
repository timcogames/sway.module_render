#include <sway/graphics/rendersubsystem.h>
#include <sway/graphics/rendersubqueuegroups.h>
#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/renderqueue.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

namespace global {
	core::Plugin * _pluginInstance = nullptr;
	gapi::ConcreatePluginFunctionSet * _pluginFunctionSet = nullptr;

	gapi::ConcreatePluginFunctionSet * getGapiFunctionSet() {
		if (_pluginFunctionSet == nullptr)
			_pluginInstance->initialize(_pluginFunctionSet = new gapi::ConcreatePluginFunctionSet());

		return _pluginFunctionSet;
	}
} // namespace global

RenderSubsystem::RenderSubsystem(const std::string & plugname, core::foundation::Context * context) : core::foundation::Object(context) {
	global::_pluginInstance = new core::Plugin(plugname);

	_capability = global::getGapiFunctionSet()->createCapability();
}

RenderSubsystem::~RenderSubsystem() {
	_queues.clear();

	//SAFE_DELETE(global::_pluginFunctionSet);
	//SAFE_DELETE(global::_pluginInstance);
}

RenderQueueRef_t RenderSubsystem::createQueue(u32_t priority) {
	_queues.push_back(std::make_shared<RenderQueue>(priority));
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
		_renderSubqueues(_queues[i], RenderSubqueueGroup_t::kOpaque);
		_renderSubqueues(_queues[i], RenderSubqueueGroup_t::kTransparent);
	}
}

void RenderSubsystem::_renderSubqueues(RenderQueueRef_t queue, RenderSubqueueGroup_t group) {
	const RenderSubqueueRefVec_t & subqueues = queue->getSubqueues(group);

	if (subqueues.size() > 0) {
		for (const RenderSubqueueRef_t & subqueue : subqueues)
			subqueue->render();
	}
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
