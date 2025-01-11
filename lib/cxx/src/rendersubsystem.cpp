#include <sway/render/global.hpp>
#include <sway/render/ppe/postprocessingpass.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubqueuegroups.hpp>
#include <sway/render/rendersubsystem.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

RenderSubsystem::RenderSubsystem(core::Plugin *plug, core::typedefs::ContextPtr_t ctx)
    : core::Subsystem(ctx) {
  global::pluginInstance_ = plug;
}

RenderSubsystem::~RenderSubsystem() {
  queues_.clear();

  SAFE_DELETE_OBJECT(idGenerator_[2]);
  SAFE_DELETE_OBJECT(idGenerator_[1]);
  SAFE_DELETE_OBJECT(idGenerator_[0]);

  SAFE_DELETE_OBJECT(rasterizer_);
  SAFE_DELETE_OBJECT(viewport_);

  SAFE_DELETE_OBJECT(global::pluginFunctionSet_);
  SAFE_DELETE_OBJECT(global::pluginInstance_);
}

void RenderSubsystem::setGraphicsApiContext(global::GapiPluginFunctionSet *pluginFuncs) {
  deviceContext_ = pluginFuncs;
}

auto RenderSubsystem::initialize() -> bool {
  viewport_ = deviceContext_->createViewport();
  viewport_->set(800, 600);

  rasterizer_ = deviceContext_->createRasterizerState();

  idGenerator_[0] = deviceContext_->createBufferIdGenerator();
  idGenerator_[1] = deviceContext_->createFrameBufferIdGenerator();
  idGenerator_[2] = deviceContext_->createTextureIdGenerator();

  geomBuilder_ = GeomBuilder::create(deviceContext_, getIdGenerator(0 /* GEOMETRY */));
  geomBuilder_->reserve(Constants::MAX_BUFFER_OBJECTS);

  renderModule_ = std::make_unique<experience::RenderModule>();
  renderModule_->initialGraphicsApiContext(deviceContext_);
  renderModule_->prepare();

  return true;
}

void RenderSubsystem::createPostProcessing(typedefs::RenderSubqueueSharedPtr_t subqueue, core::Dictionary glob) {
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
  ppe_->add(frstPass, 0 /*core::toBase(RenderStage::IDX_COLOR)*/);

  // auto scndPass = std::make_shared<PostProcessingPass>("scnd", fullscreenQuad_);
  // scndPass->setEnabled(true);
  // auto scndTarget = std::make_shared<RenderTarget>();
  // scndTarget->setScissorViewport(viewport_);
  // std::static_pointer_cast<PostProcessingPass>(scndPass)->setRenderTarget(scndTarget);
  // std::static_pointer_cast<PostProcessingPass>(scndPass)->setRenderState(std::make_shared<RenderState>());
  // ppe_->add(scndPass, core::toBase(RenderStage::IDX_DEPTH));
}

auto RenderSubsystem::getQueueByPriority(u32_t priority) -> typedefs::RenderQueueSharedPtr_t {
  for (auto queue : queues_) {
    if (queue->getPriority() == priority) {
      return queue;
    }
  }

  return nullptr;
}

auto RenderSubsystem::createQueue(u32_t priority) -> typedefs::RenderQueueSharedPtr_t {
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
  renderModule_->getState().activeRenderer->render();

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

void RenderSubsystem::renderSubqueues_(typedefs::RenderQueueSharedPtr_t queue, RenderSubqueueGroup group, u32_t stage,
    typedefs::RenderStateSharedPtr_t state) {
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
