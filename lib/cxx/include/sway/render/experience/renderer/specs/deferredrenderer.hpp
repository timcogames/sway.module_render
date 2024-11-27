#ifndef SWAY_RENDER_EXPERIENCE_DEFERREDRENDERER_HPP
#define SWAY_RENDER_EXPERIENCE_DEFERREDRENDERER_HPP

#include <sway/render/experience/renderer/renderer.hpp>
#include <sway/render/experience/renderer/renderertypes.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class DeferredRenderer final : public Renderer {
public:
#pragma region "Ctors/Dtor"

  DeferredRenderer();

  DTOR_VIRTUAL_DEFAULT(DeferredRenderer);

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_DEFERREDRENDERER_HPP
