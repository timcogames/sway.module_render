#ifndef SWAY_RENDER_EXPERIENCE_DEFERGBUFFERPASS_HPP
#define SWAY_RENDER_EXPERIENCE_DEFERGBUFFERPASS_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/pass/specs/scenegeompass.hpp>

namespace sway::render {
NS_BEGIN(experience)

class DeferGBufferPass : public SceneGeomPass {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  DeferGBufferPass(const PassDescriptor &desc)
      : SceneGeomPass(desc) {}

  DTOR_VIRTUAL_DEFAULT(DeferGBufferPass);

  /** @} */
#pragma endregion
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_DEFERGBUFFERPASS_HPP
