#include <sway/render/global.hpp>
#include <sway/render/ppe/postprocessingpass.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubqueuegroups.hpp>
#include <sway/render/rendersubsystem.hpp>
#include <sway/render/temp/forwardrenderer.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

RenderSubsystem::RenderSubsystem(core::Plugin *plug, core::foundation::Context::Ptr_t context)
    : core::foundation::Subsystem(context) {
  global::pluginInstance_ = plug;

  idGenerator_[0] = global::getGapiPluginFunctionSet()->createBufferIdGenerator();
  idGenerator_[1] = global::getGapiPluginFunctionSet()->createFrameBufferIdGenerator();
  idGenerator_[2] = global::getGapiPluginFunctionSet()->createTextureIdGenerator();

  addRenderer(std::make_unique<ForwardRenderer>());
  setActiveRenderer(core::detail::toBase(RendererType::Enum::FORWARD));
}

RenderSubsystem::~RenderSubsystem() {
  queues_.clear();

  SAFE_DELETE_OBJECT(idGenerator_[2]);
  SAFE_DELETE_OBJECT(idGenerator_[1]);
  SAFE_DELETE_OBJECT(idGenerator_[0]);

  SAFE_DELETE_OBJECT(capability_);

  SAFE_DELETE_OBJECT(global::pluginFunctionSet_);
  SAFE_DELETE_OBJECT(global::pluginInstance_);
}

auto RenderSubsystem::initialize() -> bool {
  capability_ = global::getGapiPluginFunctionSet()->createCapability();
  rasterizer_ = global::getGapiPluginFunctionSet()->createRasterizerState();
  viewport_ = global::getGapiPluginFunctionSet()->createViewport();
  viewport_->set(800, 600);

  geomBuilder_ = GeomBuilder::create(getIdGenerator(0 /* GEOMETRY */));
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

  auto clearColor = math::col4f_t(0.0F, 0.0F, 0.0F, 255.0F);
  auto clearFlag = gapi::ClearFlag::COLOR;
  viewport_->setClearColor(clearColor);
  viewport_->clear(clearFlag);

  ppe_->postRender();
}

void RenderSubsystem::renderSubqueues_(
    RenderQueue::SharedPtr_t queue, RenderSubqueueGroup group, u32_t stage, RenderState::SharedPtr_t state) {
  const auto &subqueues = queue->getSubqueues(group);
  if (subqueues.empty()) {
    return;
  }

  for (const auto &subqueue : subqueues) {
    subqueue->render(stage, state->getContext());
  }
}

NS_END()  // namespace render
NS_END()  // namespace sway
