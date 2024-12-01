#ifndef SWAY_RENDER_EXPERIENCE_RENDERERMANAGER_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERERMANAGER_HPP

#include <sway/render/experience/renderer/_typedefs.hpp>
#include <sway/render/experience/renderer/renderer.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class RendererManager final {
public:
#pragma region "Ctors/Dtor"

  RendererManager() = default;

  DTOR_DEFAULT(RendererManager);

#pragma endregion

  auto add(RendererTypedefs::UniquePtr_t renderer) -> i32_t;

  void restore(i32_t idx, RendererTypedefs::UniquePtr_t renderer);

  void erase(i32_t idx);

  auto find(i32_t type) -> RendererTypedefs::Container_t::iterator;

  auto size() const -> std::size_t;

private:
  RendererTypedefs::Container_t renderers_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_RENDERERMANAGER_HPP
