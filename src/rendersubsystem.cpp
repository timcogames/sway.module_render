#include <sway/graphics/rendersubsystem.h>
#include <sway/graphics/rendersubqueuegroups.h>
#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/renderqueue.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

static core::Plugin * pluginInstance = nullptr;

core::Plugin * getPluginInstance() {
	if (pluginInstance == nullptr) {
		char path[PATH_MAX + 1];
		strncpy(path, "/home/bonus85/Projects/sway.modules/sway.module_graphics/bin", PATH_MAX);
		//pluginInstance = new core::Plugin((boost::format("%s/module_gapi_dummy.so.0.1.0") % path).str());
		pluginInstance = new core::Plugin((boost::format("%s/module_gapi_gl.so.0.14.33") % path).str());

	}

	return pluginInstance;
}

RenderSubsystem::RenderSubsystem(core::foundation::Context * context) : core::foundation::Object(context) {
	gapi::ConcreatePluginFunctionSet * pluginFuncSet = new gapi::ConcreatePluginFunctionSet();
	core::Plugin * plugin = getPluginInstance();
	if (plugin->isLoaded())
		plugin->initialize(pluginFuncSet);

	_capability = pluginFuncSet->createCapability();
}

RenderSubsystem::~RenderSubsystem() {
	_queues.clear();
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
		BOOST_FOREACH (const RenderSubqueueRef_t & subqueue, subqueues)
			subqueue->render();
	}
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
