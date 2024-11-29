#ifndef SWAY_RENDER_EXPERIENCE_RENDERCONTEXT_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERCONTEXT_HPP

#include <sway/render/experience/renderer/_typedefs.hpp>
#include <sway/render/experience/technique/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct RenderContext {
  TechniqueManagerTypedefs::UniquePtr_t techniqueMngr;
  RendererManagerTypedefs::UniquePtr_t rendererMngr;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_RENDERCONTEXT_HPP
