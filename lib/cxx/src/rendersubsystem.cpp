#include <sway/render/global.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubqueuegroups.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

RenderSubsystem::RenderSubsystem(core::Plugin *plug, core::foundation::Context *context)
    : core::foundation::Subsystem(context) {
  global::pluginInstance_ = plug;
}

RenderSubsystem::~RenderSubsystem() {
  queues_.clear();

  SAFE_DELETE_OBJECT(idGenerator_);
  SAFE_DELETE_OBJECT(capability_);

  SAFE_DELETE_OBJECT(global::pluginFunctionSet_);
  SAFE_DELETE_OBJECT(global::pluginInstance_);
}

auto RenderSubsystem::initialize() -> bool {
  capability_ = global::getGapiPluginFunctionSet()->createCapability();
  idGenerator_ = global::getGapiPluginFunctionSet()->createIdGenerator();

  auto target = std::make_shared<RenderTarget>();
  target->setScissorViewport(global::getGapiPluginFunctionSet()->createViewport());

  auto state = std::make_shared<RenderState>();

  for (auto i = 0; i < core::detail::toBase(RenderStage::MAX_STAGE); i++) {
    passes_[i] = std::make_shared<RenderPass>();
    passes_[i]->setRenderTarget(target);
    passes_[i]->setRenderState(state);
  }

  geomBuilder_ = GeomBuilder::create(idGenerator_);
  geomBuilder_->reserve(Constants::MAX_BUFFER_OBJECTS);

  return true;
}

auto RenderSubsystem::createQueue(u32_t priority) -> RenderQueueRef_t {
  if (this->getQueueByPriority(priority)) {
    return nullptr;
  }

  queues_.push_back(std::make_shared<RenderQueue>(priority));
  return queues_.back();
}

auto RenderSubsystem::getQueueByPriority(u32_t priority) -> RenderQueueRef_t {
  for (auto queue : queues_) {
    if (queue->getPriority() == priority) {
      return queue;
    }
  }

  return nullptr;
}

void RenderSubsystem::sortQueues() {
  if (queues_.size() >= 2) {
    std::sort(queues_.begin(), queues_.end(), RenderQueue::PriorityInDescendingOrder());
  }
}

void RenderSubsystem::render() {
  for (auto i = 0; i < core::detail::toBase(RenderStage::MAX_STAGE); i++) {
    auto target = passes_[i]->getRenderTarget();
    auto state = passes_[i]->getRenderState();

    target->activate();

    for (auto &queue : queues_) {
      renderSubqueues_(queue, RenderSubqueueGroup::OPAQUE, i, state);
      renderSubqueues_(queue, RenderSubqueueGroup::TRANSPARENT, i, state);
    }

    target->deactivate();
  }
}

void RenderSubsystem::renderSubqueues_(
    RenderQueueRef_t queue, RenderSubqueueGroup group, u32_t stage, std::shared_ptr<RenderState> state) {
  const RenderSubqueueRefVec_t &subqueues = queue->getSubqueues(group);
  if (subqueues.empty()) {
    return;
  }

  for (const RenderSubqueueRef_t &subqueue : subqueues) {
    subqueue->render(stage, state->getContext());
  }
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
