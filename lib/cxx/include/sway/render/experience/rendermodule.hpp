#ifndef SWAY_RENDER_EXPERIENCE_RENDERMODULE_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERMODULE_HPP

#include <sway/render/experience/_typedefs.hpp>
#include <sway/render/experience/renderer/renderertypes.hpp>
#include <sway/render/experience/renderstate.hpp>
#include <sway/render/global.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class RenderModule {
public:
#pragma region "Static methods"

  static auto getInternalContext() -> RenderContextTypedefs::Ptr_t;

#pragma endregion

#pragma region "Ctors/Dtor"

  RenderModule() = default;

  DTOR_DEFAULT(RenderModule);

#pragma endregion

  void initialGraphicsApiContext(global::GapiPluginFunctionSet *pluginFuncs);

  void prepare();

  void setActiveRenderer(i32_t idx);

#pragma region "Getters/Setters"

  auto getState() const -> const RenderState & { return state_; }

#pragma endregion

private:
  mutable RenderState state_;  ///< Current state.
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_RENDERMODULE_HPP
