#include <sway/render/global.hpp>
#include <sway/render/ppe/postprocessingpass.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubqueuegroups.hpp>
#include <sway/render/rendersubsystem.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

RenderSubsystem::RenderSubsystem(core::Plugin *plug, core::foundation::Context::Ptr_t context)
    : core::foundation::Subsystem(context) {
  global::pluginInstance_ = plug;
}

RenderSubsystem::~RenderSubsystem() {
  queues_.clear();

  SAFE_DELETE_OBJECT(textureIdGenerator_);
  SAFE_DELETE_OBJECT(bufferIdGenerator_);
  SAFE_DELETE_OBJECT(capability_);

  SAFE_DELETE_OBJECT(global::pluginFunctionSet_);
  SAFE_DELETE_OBJECT(global::pluginInstance_);
}

auto RenderSubsystem::initialize() -> bool {
  capability_ = global::getGapiPluginFunctionSet()->createCapability();
  bufferIdGenerator_ = global::getGapiPluginFunctionSet()->createBufferIdGenerator();
  textureIdGenerator_ = global::getGapiPluginFunctionSet()->createTextureIdGenerator();
  viewport_ = global::getGapiPluginFunctionSet()->createViewport();

  passMngr_ = std::make_shared<RenderPassManager>();

  geomBuilder_ = GeomBuilder::create(bufferIdGenerator_);
  geomBuilder_->reserve(Constants::MAX_BUFFER_OBJECTS);

  return true;
}

void RenderSubsystem::createPostProcessing(RenderSubqueue::SharedPtr_t subqueue, core::misc::Dictionary glob) {
  ppe_ = std::make_shared<PostProcessing>(viewport_);

  renderState_ = std::make_shared<RenderState>();

  fullscreenQuad_ = std::make_shared<render::ScreenQuad>();
  fullscreenQuad_->initialize(glob, geomBuilder_);

  auto frstPass = std::make_shared<PostProcessingPass>("frst", fullscreenQuad_);
  frstPass->setEnabled(true);
  auto frstTarget = std::make_shared<RenderTarget>();
  frstTarget->setScissorViewport(viewport_);
  frstTarget->attachColorBufferObject(this);
  std::static_pointer_cast<PostProcessingPass>(frstPass)->setRenderTarget(frstTarget);
  std::static_pointer_cast<PostProcessingPass>(frstPass)->setRenderState(renderState_);
  ppe_->add(frstPass, core::detail::toBase(RenderStage::IDX_COLOR));

  // auto scndPass = std::make_shared<PostProcessingPass>("scnd", fullscreenQuad_);
  // scndPass->setEnabled(true);
  // auto scndTarget = std::make_shared<RenderTarget>();
  // scndTarget->setScissorViewport(viewport_);
  // std::static_pointer_cast<PostProcessingPass>(scndPass)->setRenderTarget(scndTarget);
  // std::static_pointer_cast<PostProcessingPass>(scndPass)->setRenderState(std::make_shared<RenderState>());
  // ppe_->add(scndPass, core::detail::toBase(RenderStage::IDX_DEPTH));
}

auto RenderSubsystem::getQueueByPriority(u32_t priority) -> RenderQueue::SharedPtr_t {
  for (auto queue : queues_) {
    if (queue->getPriority() == priority) {
      return queue;
    }
  }

  return nullptr;
}

auto RenderSubsystem::createQueue(u32_t priority) -> RenderQueue::SharedPtr_t {
  if (this->getQueueByPriority(priority)) {
    return nullptr;
  }

  queues_.push_back(std::make_shared<RenderQueue>(priority));
  return queues_.back();
}

void RenderSubsystem::createQueuePass(const std::string &name, i32_t idx) {
  auto pass = std::make_shared<RenderQueuePass>(name);
  passMngr_->addPass(std::static_pointer_cast<RenderPass>(pass), idx);
}

void RenderSubsystem::sortQueues() {
  if (queues_.size() >= 2) {
    std::sort(queues_.begin(), queues_.end(), RenderQueue::PriorityInDescendingOrder());
  }
}

void RenderSubsystem::render() {
  for (auto i = 0; i < passMngr_->getNumPasses(); i++) {
    auto pass = passMngr_->getPass(i);
  }

  ppe_->preRender();

  for (auto i = 0; i < ppe_->getNumPasses(); i++) {
    auto target = std::static_pointer_cast<PostProcessingPass>(ppe_->getPass(i))->getRenderTarget();
    auto state = std::static_pointer_cast<PostProcessingPass>(ppe_->getPass(i))->getRenderState();

    target->activate(state->getContext());

    for (auto &queue : queues_) {
      renderSubqueues_(queue, RenderSubqueueGroup::OPAQUE, i, state);
      renderSubqueues_(queue, RenderSubqueueGroup::TRANSPARENT, i, state);
    }

    target->deactivate();
  }

  auto clearFlags = core::detail::toBase(gapi::ClearFlag::COLOR);
  if (clearFlags & core::detail::toBase(gapi::ClearFlag::COLOR)) {
    viewport_->setClearColor(math::col4f_t(50.0F, 50.0F, 50.0F, 1.0F));
  }

  auto clearDepth = 0;
  if (clearFlags & core::detail::toBase(gapi::ClearFlag::DEPTH)) {
    renderState_->getContext()->setClearDepth(clearDepth);
    renderState_->getContext()->setDepthMask(true);
  }

  auto clearStencil = 0;
  if (clearFlags & core::detail::toBase(gapi::ClearFlag::STENCIL)) {
    renderState_->getContext()->setClearStencil(clearStencil);
    renderState_->getContext()->setStencilMask(0x0);
  }

  viewport_->clear(core::detail::toEnum<gapi::ClearFlag>(clearFlags));

  ppe_->postRender();
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

NS_END()  // namespace render
NS_END()  // namespace sway
