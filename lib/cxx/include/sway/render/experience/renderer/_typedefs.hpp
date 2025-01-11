#ifndef SWAY_RENDER_EXPERIENCE_RENDERER_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERER_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
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
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_RENDERER_TYPEDEFS_HPP
