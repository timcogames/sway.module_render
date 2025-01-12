#ifndef SWAY_RENDER_EXPERIENCE_RENDERER_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERER_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
NS_BEGIN(experience)

class Renderer;
namespace RendererTypedefs {
using Ptr_t = Renderer *;
using UniquePtr_t = std::unique_ptr<Renderer>;
using Container_t = std::vector<UniquePtr_t>;
}  // namespace RendererTypedefs

class RendererManager;
namespace RendererManagerTypedefs {
using UniquePtr_t = std::unique_ptr<RendererManager>;
}  // namespace RendererManagerTypedefs

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_RENDERER_TYPEDEFS_HPP
