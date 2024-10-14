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

  for (auto i = 0; i < RendererTypeCountWithoutNone; i++) {
    renderers_.push_back(std::make_shared<Renderer>(core::detail::toEnum<RendererType::Enum>(i)));
  }

  // auto forward = getRenderer(RendererType::Enum::FORWARD);
  // auto forwardStageQueue = forward->getStageQueue(StageGroupIndex::Enum::IDX_SHADING);
  // auto forwardStage = forwardStageQueue.addStage();

  // forwardStage->addPass(std::make_shared<GeomPass>("geom"));
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
  rasterizer_ = global::getGapiPluginFunctionSet()->createRasterizerState();
  bufferIdGenerator_ = global::getGapiPluginFunctionSet()->createBufferIdGenerator();
  frameBufferIdGenerator_ = global::getGapiPluginFunctionSet()->createFrameBufferIdGenerator();
  textureIdGenerator_ = global::getGapiPluginFunctionSet()->createTextureIdGenerator();
  viewport_ = global::getGapiPluginFunctionSet()->createViewport();
  viewport_->set(800, 600);

  geomBuilder_ = GeomBuilder::create(bufferIdGenerator_);
  geomBuilder_->reserve(Constants::MAX_BUFFER_OBJECTS);

  return true;
}

void RenderSubsystem::createPostProcessing(RenderSubqueue::SharedPtr_t subqueue, core::misc::Dictionary glob) {
  ppe_ = std::make_shared<PostProcessing>(viewport_);

  renderState_ = std::make_shared<RenderState>();
  renderState_->getContext()->setDepthEnable(true);

  fullscreenQuad_ = std::make_shared<render::ScreenQuad>();
  fullscreenQuad_->initialize(glob, geomBuilder_);

  auto frstPass = std::make_shared<PostProcessingPass>("frst", fullscreenQuad_);
  frstPass->setEnabled(true);
  auto frstTarget = std::make_shared<RenderTarget>();
  frstTarget->setScissorViewport(viewport_);
  frstTarget->attachColorBufferObject(this);
  std::static_pointer_cast<PostProcessingPass>(frstPass)->setRenderTarget(frstTarget);
  std::static_pointer_cast<PostProcessingPass>(frstPass)->setRenderState(renderState_);
  ppe_->add(frstPass, 0 /*core::detail::toBase(RenderStage::IDX_COLOR)*/);

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

void RenderSubsystem::sortQueues() {
  if (queues_.size() >= 2) {
    std::sort(queues_.begin(), queues_.end(), RenderQueue::PriorityInDescendingOrder());
  }
}

void RenderSubsystem::render() {
  // for (auto i = 0; i < passMngr_->getNumPasses(); i++) {
  //   auto pass = passMngr_->getPass(i);
  // }

  // ppe_->preRender();

  // renderState_->getContext()->setCapabilityEnable(gapi::StateCapability::Enum::CULL_FACE, true);
  // gapi::RasterizerDescriptor rasterizerDesc;
  // rasterizerDesc.mode = gapi::CullFace::BACK;
  // rasterizerDesc.ccw = true;
  // rasterizer_->apply(renderState_->getContext(), rasterizerDesc);

  // for (auto i = 0; i < ppe_->getNumPasses(); i++) {

  auto target = std::static_pointer_cast<PostProcessingPass>(ppe_->getPass(0))->getRenderTarget();

  renderState_->getContext()->setDepthEnable(true);
  target->activate(renderState_->getContext());

  viewport_->setClearColor(math::col4f_t(0.0F, 0.0F, 0.0F, 0.0F));
  viewport_->clear(gapi::ClearFlag::COLOR | gapi::ClearFlag::DEPTH);

  for (auto &queue : queues_) {
    renderSubqueues_(queue, RenderSubqueueGroup::OPAQUE, 0, renderState_);
    renderSubqueues_(queue, RenderSubqueueGroup::TRANSPARENT, 0, renderState_);
  }

  target->deactivate();
  renderState_->getContext()->setDepthEnable(false);
  // }

  viewport_->setClearColor(math::col4f_t(0.0F, 0.0F, 0.0F, 255.0F));
  viewport_->clear(gapi::ClearFlag::COLOR);

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
