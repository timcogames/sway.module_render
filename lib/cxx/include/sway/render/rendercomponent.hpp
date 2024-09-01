#ifndef SWAY_RENDER_COMPONENT_HPP
#define SWAY_RENDER_COMPONENT_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderComponent : public core::foundation::Object {
  DECLARE_CLASS_METADATA(RenderComponent, core::foundation::Object)

public:
  // PURE_VIRTUAL(void onAwake());

  // PURE_VIRTUAL(void onStart());

  // PURE_VIRTUAL(void onUpdate(f32_t dtime));

  PURE_VIRTUAL(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtm));

  // PURE_VIRTUAL(void onDestroy());
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_COMPONENT_HPP
