#include <sway/render/global.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubqueuegroups.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

RenderSubsystem::RenderSubsystem(core::Plugin *plug, core::foundation::Context::Ptr_t context)
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
  viewport_ = global::getGapiPluginFunctionSet()->createViewport();

  geomBuilder_ = GeomBuilder::create(idGenerator_);
  geomBuilder_->reserve(Constants::MAX_BUFFER_OBJECTS);

  return true;
}

auto RenderSubsystem::createPostProcessing(
    RenderSubqueue::SharedPtr_t subqueue, Material::SharedPtr_t material) -> FullscreenQuadrilateral::SharedPtr_t {
  ppe_ = std::make_shared<PostProcessing>(viewport_);
  for (auto i = 0; i < MAX_RENDER_STAGES; i++) {
    ppe_->addPass(i);
  }

  fullscreenQuad_ = std::make_shared<FullscreenQuadrilateral>();
  fullscreenQuad_->initialize(geomBuilder_, subqueue, material);

  return fullscreenQuad_;
}

auto RenderSubsystem::createQueue(u32_t priority) -> RenderQueue::SharedPtr_t {
  if (this->getQueueByPriority(priority)) {
    return nullptr;
  }

  queues_.push_back(std::make_shared<RenderQueue>(priority));
  return queues_.back();
}

auto RenderSubsystem::getQueueByPriority(u32_t priority) -> RenderQueue::SharedPtr_t {
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
  for (auto i = 0; i < MAX_RENDER_STAGES; i++) {
    auto target = ppe_->passes_[i]->getRenderTarget();
    auto state = ppe_->passes_[i]->getRenderState();

    target->activate();

    for (auto &queue : queues_) {
      renderSubqueues_(queue, RenderSubqueueGroup::OPAQUE, i, state);
      renderSubqueues_(queue, RenderSubqueueGroup::TRANSPARENT, i, state);
    }

    target->deactivate();
  }
}

void RenderSubsystem::renderSubqueues_(
    RenderQueue::SharedPtr_t queue, RenderSubqueueGroup group, u32_t stage, std::shared_ptr<RenderState> state) {
  const RenderSubqueueSharedPtrVec_t &subqueues = queue->getSubqueues(group);
  if (subqueues.empty()) {
    return;
  }

  for (const RenderSubqueue::SharedPtr_t &subqueue : subqueues) {
    subqueue->render(stage, state->getContext());
  }
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
