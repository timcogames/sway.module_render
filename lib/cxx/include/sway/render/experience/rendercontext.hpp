#ifndef SWAY_RENDER_EXPERIENCE_RENDERCONTEXT_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERCONTEXT_HPP

#include <sway/render/experience/renderer/_typedefs.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct GapiContext {
  gapi::CapabilityPtr_t capability;
  gapi::DrawCallPtr_t drawCall;

  void disponse() {
    SAFE_DELETE_OBJECT(drawCall);
    SAFE_DELETE_OBJECT(capability);
  }
};

struct RenderContext final : public GapiContext {
  TechniqueManagerTypedefs::UniquePtr_t techniqueMngr;
  RendererManagerTypedefs::UniquePtr_t rendererMngr;

  void disponse() { GapiContext::disponse(); }
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_RENDERCONTEXT_HPP
