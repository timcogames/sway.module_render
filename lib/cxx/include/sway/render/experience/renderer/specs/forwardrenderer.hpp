#ifndef SWAY_RENDER_EXPERIENCE_FORWARDRENDERER_HPP
#define SWAY_RENDER_EXPERIENCE_FORWARDRENDERER_HPP

#include <sway/render/experience/renderer/renderer.hpp>
#include <sway/render/experience/renderer/renderertypes.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class ForwardRenderer final : public Renderer {
public:
#pragma region "Ctors/Dtor"

  ForwardRenderer();

  DTOR_VIRTUAL_DEFAULT(ForwardRenderer);

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_FORWARDRENDERER_HPP
