#ifndef SWAY_RENDER_EXPERIENCE_DEFERGBUFFERPASS_HPP
#define SWAY_RENDER_EXPERIENCE_DEFERGBUFFERPASS_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/pass/specs/scenegeompass.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class DeferGBufferPass : public SceneGeomPass {
public:
#pragma region "Ctors/Dtor"

  DeferGBufferPass(const PassDescriptor &desc)
      : SceneGeomPass(desc) {}

  DTOR_VIRTUAL_DEFAULT(DeferGBufferPass);

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_DEFERGBUFFERPASS_HPP
