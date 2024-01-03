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

  // testing::StrictMock<global::MockPluginFunctionSet> mock;
  // EXPECT_CALL(mock, createCapability()).WillOnce(testing::Return(nullptr));
}

RenderSubsystem::~RenderSubsystem() {
  queues_.clear();

  idGenerator_.reset();
  capability_.reset();

  SAFE_DELETE_OBJECT(global::pluginFunctionSet_);
  SAFE_DELETE_OBJECT(global::pluginInstance_);
}

auto RenderSubsystem::initialize() -> bool {
  capability_ = global::getGapiFunctionSet()->createCapability();
  idGenerator_ = global::getGapiFunctionSet()->createIdGenerator();

  passes_[core::detail::toUnderlying(RenderStage::DEPTH)] = std::make_shared<RenderPass>();
  passes_[core::detail::toUnderlying(RenderStage::COLOR)] = std::make_shared<RenderPass>();
  passes_[core::detail::toUnderlying(RenderStage::STENCIL)] = std::make_shared<RenderPass>();

  auto target = std::make_shared<RenderTarget>();
  target->setScissorViewport(global::getGapiFunctionSet()->createViewport());

  for (auto i = 0; i < core::detail::toUnderlying(RenderStage::MAX_STAGE); i++) {
    passes_[i]->setRenderTarget(target);
  }

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
  for (auto i = 0; i < core::detail::toUnderlying(RenderStage::MAX_STAGE); i++) {
    auto target = passes_[i]->getRenderTarget();
    target->activate();

    for (auto &queue : queues_) {
      renderSubqueues_(queue, RenderSubqueueGroup::OPAQUE, i);
      renderSubqueues_(queue, RenderSubqueueGroup::TRANSPARENT, i);
    }

    target->deactivate();
  }
}

void RenderSubsystem::renderSubqueues_(RenderQueueRef_t queue, RenderSubqueueGroup group, u32_t stage) {
  const RenderSubqueueRefVec_t &subqueues = queue->getSubqueues(group);
  if (subqueues.empty()) {
    return;
  }

  for (const RenderSubqueueRef_t &subqueue : subqueues) {
    subqueue->render(stage);
  }
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
