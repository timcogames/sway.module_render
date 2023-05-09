#ifndef SWAY_RENDER_COMPONENT_HPP
#define SWAY_RENDER_COMPONENT_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderComponent : public core::foundation::Object {
public:
  DECLARE_CLASS_METADATA(RenderComponent, core::foundation::Object)

  // PURE_VIRTUAL(void onAwake());

  // PURE_VIRTUAL(void onStart());

  // PURE_VIRTUAL(void onUpdate(f32_t dtime));

  PURE_VIRTUAL(void onUpdate(math::mat4f_t transform, math::mat4f_t proj, f32_t deltaTime));

  // PURE_VIRTUAL(void onDestroy());
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_COMPONENT_HPP
