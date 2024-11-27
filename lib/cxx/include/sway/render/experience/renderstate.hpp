#ifndef SWAY_RENDER_EXPERIENCE_RENDERSTATE_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERSTATE_HPP

#include <sway/render/experience/renderer/_typedefs.hpp>
#include <sway/render/experience/renderer/renderer.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct RenderState {
  RendererTypedefs::UniquePtr_t activeRenderer{nullptr};
  i32_t activeRendererIdx{-1};
  std::atomic_bool initialized{false};
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_RENDERSTATE_HPP