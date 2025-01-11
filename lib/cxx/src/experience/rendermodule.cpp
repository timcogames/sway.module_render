#include <sway/render/experience/pipeline/pipelinelibrary.hpp>
#include <sway/render/experience/rendercontext.hpp>
#include <sway/render/experience/renderer/renderermanager.hpp>
#include <sway/render/experience/renderer/renderertypes.hpp>
#include <sway/render/experience/renderer/specs/deferredrenderer.hpp>
#include <sway/render/experience/renderer/specs/forwardrenderer.hpp>
#include <sway/render/experience/rendermodule.hpp>
#include <sway/render/experience/technique/techniquemanager.hpp>
#include <sway/render/global.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

RenderContext context_;  ///< Internat context.

auto RenderModule::getInternalContext() -> RenderContextTypedefs::Ptr_t { return &context_; }

void RenderModule::initialGraphicsApiContext(global::GapiPluginFunctionSet *pluginFuncs) {
  context_.capability = pluginFuncs->createCapability();
  context_.viewport = pluginFuncs->createViewport();
  context_.drawCall = pluginFuncs->createDrawCall();
}

void RenderModule::prepare() {
  context_.pipelineLibrary = std::make_unique<PipelineLibrary>();
  context_.techniqueMngr = std::make_unique<TechniqueManager>();
  context_.rendererMngr = std::make_unique<RendererManager>();
  context_.rendererMngr->add(std::unique_ptr<Renderer>(new ForwardRenderer()));
  context_.rendererMngr->add(std::unique_ptr<Renderer>(new DeferredRenderer()));

  setActiveRenderer(core::toBase(RendererType::Enum::IDX_FWD));
}

void RenderModule::setActiveRenderer(i32_t idx) {
  if (idx < 0 || idx >= context_.rendererMngr->getSize() || idx == state_.activeRendererIdx) {
    return;
  }

  // Возвращаем владение обратно в контейнер.
  context_.rendererMngr->restore(state_.activeRendererIdx, std::move(state_.activeRenderer));

  // Получаем указатель, но не владеем им после вызова release().
  auto itm = std::move(*context_.rendererMngr->find(idx));
  // Освобождаем владение объектом.
  auto raw = itm.release();

  state_.activeRenderer.reset(raw);
  state_.activeRendererIdx = idx;
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
