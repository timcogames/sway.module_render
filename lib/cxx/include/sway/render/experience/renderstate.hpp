#ifndef SWAY_RENDER_EXPERIENCE_RENDERSTATE_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERSTATE_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/renderer/_typedefs.hpp>
#include <sway/render/experience/renderer/renderer.hpp>

namespace sway::render {
NS_BEGIN(experience)

struct RenderState {
  RendererTypedefs::UniquePtr_t activeRenderer{nullptr};
  i32_t activeRendererIdx{-1};
  std::atomic_bool initialized{false};
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_RENDERSTATE_HPP