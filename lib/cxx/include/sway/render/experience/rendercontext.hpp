#ifndef SWAY_RENDER_EXPERIENCE_RENDERCONTEXT_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERCONTEXT_HPP

#include <sway/render/experience/pipeline/_typedefs.hpp>
#include <sway/render/experience/renderer/_typedefs.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct DeviceContext {
  gapi::CapabilityPtr_t capability;
  gapi::DrawCallPtr_t drawCall;
  gapi::ViewportPtr_t viewport;

  void disponse() {
    SAFE_DELETE_OBJECT(drawCall);
    SAFE_DELETE_OBJECT(capability);
    SAFE_DELETE_OBJECT(viewport);
  }
};

struct TechniqueContext {
  PipelineLibraryTypedefs::UniquePtr_t pipelineLibrary;
};

struct RenderContext final : public DeviceContext, public TechniqueContext {
  TechniqueManagerTypedefs::UniquePtr_t techniqueMngr;
  RendererManagerTypedefs::UniquePtr_t rendererMngr;

  void disponse() { DeviceContext::disponse(); }
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_RENDERCONTEXT_HPP
