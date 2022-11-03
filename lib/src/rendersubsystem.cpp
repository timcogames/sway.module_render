#include <sway/graphics/renderqueue.hpp>
#include <sway/graphics/rendersubqueue.hpp>
#include <sway/graphics/rendersubqueuegroups.hpp>
#include <sway/graphics/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

namespace global {
core::Plugin *_pluginInstance = nullptr;
gapi::ConcreatePluginFunctionSet *_pluginFunctionSet = nullptr;

gapi::ConcreatePluginFunctionSet *getGapiFunctionSet() {
  if (_pluginFunctionSet == nullptr) {
    _pluginInstance->initialize(_pluginFunctionSet = new gapi::ConcreatePluginFunctionSet());
  }

  return _pluginFunctionSet;
}
}  // namespace global

RenderSubsystem::RenderSubsystem(const std::string &plugname, core::foundation::Context *context)
    : core::foundation::Subsystem(context) {
  global::_pluginInstance = new core::Plugin(plugname);
  auto *pluginFuncSet = global::getGapiFunctionSet();

  capability_ = pluginFuncSet->createCapability();
}

RenderSubsystem::~RenderSubsystem() {
  queues_.clear();

  // SAFE_DELETE(global::_pluginFunctionSet);
  // SAFE_DELETE(global::_pluginInstance);
}

RenderQueueRef_t RenderSubsystem::createQueue(u32_t priority) {
  queues_.push_back(std::make_shared<RenderQueue>(priority));
  return queues_.back();
}

RenderQueueRef_t RenderSubsystem::getQueueByIdx(u32_t index) { return queues_[index]; }

RenderQueueRefVector_t RenderSubsystem::getQueues() { return queues_; }

void RenderSubsystem::sortQueues() {
  if (queues_.size() >= 2) {
    std::sort(queues_.begin(), queues_.end(), RenderQueue::PriorityInDescendingOrder());
  }
}

void RenderSubsystem::render() {
  for (u32_t i = 0; i < queues_.size(); ++i) {
    renderSubqueues_(queues_[i], RenderSubqueueGroup_t::kOpaque);
    renderSubqueues_(queues_[i], RenderSubqueueGroup_t::kTransparent);
  }
}

void RenderSubsystem::renderSubqueues_(RenderQueueRef_t queue, RenderSubqueueGroup_t group) {
  const RenderSubqueueRefVec_t &subqueues = queue->getSubqueues(group);

  if (subqueues.size() > 0) {
    for (const RenderSubqueueRef_t &subqueue : subqueues) {
      subqueue->render();
    }
  }
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
