#include <sway/render/global.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubqueuegroups.hpp>
#include <sway/render/rendersubsystem.hpp>

#define RENDER_PASS_DEFAULT 0

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

RenderSubsystem::RenderSubsystem(core::Plugin *plug, core::foundation::Context *context)
    : core::foundation::Subsystem(context) {
  global::pluginInstance_ = plug;

  // testing::StrictMock<global::MockPluginFunctionSet> mock;
  // EXPECT_CALL(mock, createCapability()).WillOnce(testing::Return(nullptr));
}

RenderSubsystem::~RenderSubsystem() {
  queues_.clear();
  passes_.clear();

  idGenerator_.reset();
  capability_.reset();

  SAFE_DELETE_OBJECT(global::pluginFunctionSet_);
  SAFE_DELETE_OBJECT(global::pluginInstance_);
}

bool RenderSubsystem::initialize() {
  capability_ = global::getGapiFunctionSet()->createCapability();
  idGenerator_ = global::getGapiFunctionSet()->createIdGenerator();

  auto pass = std::make_shared<RenderPass>();
  auto target = std::make_shared<RenderTarget>();
  target->setScissorViewport(global::getGapiFunctionSet()->createViewport());
  pass->setRenderTarget(target);
  passes_.push_back(pass);

  return true;
}

auto RenderSubsystem::createQueue(u32_t priority) -> RenderQueueRef_t {
  queues_.push_back(std::make_shared<RenderQueue>(priority));
  return queues_.back();
}

void RenderSubsystem::sortQueues() {
  if (queues_.size() >= 2) {
    std::sort(queues_.begin(), queues_.end(), RenderQueue::PriorityInDescendingOrder());
  }
}

void RenderSubsystem::render() {
  passes_[RENDER_PASS_DEFAULT]->getRenderTarget()->activate();
  for (auto &queue : queues_) {
    renderSubqueues_(queue, RenderSubqueueGroup::OPAQUE);
    renderSubqueues_(queue, RenderSubqueueGroup::TRANSPARENT);
  }

  passes_[RENDER_PASS_DEFAULT]->getRenderTarget()->deactivate();
}

void RenderSubsystem::renderSubqueues_(RenderQueueRef_t queue, RenderSubqueueGroup group) {
  const RenderSubqueueRefVec_t &subqueues = queue->getSubqueues(group);
  if (subqueues.empty()) {
    return;
  }

  for (const RenderSubqueueRef_t &subqueue : subqueues) {
    subqueue->render();
  }
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
