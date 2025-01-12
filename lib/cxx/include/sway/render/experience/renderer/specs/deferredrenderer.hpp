#ifndef SWAY_RENDER_EXPERIENCE_DEFERREDRENDERER_HPP
#define SWAY_RENDER_EXPERIENCE_DEFERREDRENDERER_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/renderer/renderer.hpp>
#include <sway/render/experience/renderer/renderertypes.hpp>

namespace sway::render {
NS_BEGIN(experience)

class DeferredRenderer final : public Renderer {
public:
#pragma region "Static methods"

  static void registerTechnique(CommandQueueTypedefs::UniquePtr_t &queue);

#pragma endregion

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  DeferredRenderer();

  DTOR_VIRTUAL_DEFAULT(DeferredRenderer);

  /** @} */
#pragma endregion

#pragma region "Overridden Renderer methods"

  MTHD_VIRTUAL_OVERRIDE(void render());

#pragma endregion
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_DEFERREDRENDERER_HPP
