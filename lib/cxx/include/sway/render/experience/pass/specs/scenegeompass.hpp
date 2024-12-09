#ifndef SWAY_RENDER_EXPERIENCE_SCENEGEOMPASS_HPP
#define SWAY_RENDER_EXPERIENCE_SCENEGEOMPASS_HPP

#include <sway/render/experience/pass/specs/graphicspass.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class SceneGeomPass : public GraphicsPass {
public:
#pragma region "Static methods"

  static auto create(const PassDescriptor &desc) -> PassTypedefs::SharedPtr_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  SceneGeomPass(const PassDescriptor &desc);

  DTOR_VIRTUAL_DEFAULT(SceneGeomPass);

#pragma endregion

  void prepare();

  void restore();

#pragma region "Overridden GraphicsPass methods"

  MTHD_VIRTUAL_OVERRIDE(void execute(DeviceContextTypedefs::Ptr_t context));

#pragma endregion

private:
  CommandBufferTypedefs::OptionalRef_t bufferOpt_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_SCENEGEOMPASS_HPP
