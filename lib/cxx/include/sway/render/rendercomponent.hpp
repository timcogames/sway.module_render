#ifndef SWAY_RENDER_COMPONENT_HPP
#define SWAY_RENDER_COMPONENT_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

namespace sway::render {

class RenderComponent : public core::Object {
  DECLARE_CLASS_METADATA(RenderComponent, core::Object)

public:
  // PURE_VIRTUAL(void onAwake());

  // PURE_VIRTUAL(void onStart());

  // PURE_VIRTUAL(void onUpdate(f32_t dtime));

  PURE_VIRTUAL(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtm));

  // PURE_VIRTUAL(void onDestroy());
};

}  // namespace sway::render

#endif  // SWAY_RENDER_COMPONENT_HPP
