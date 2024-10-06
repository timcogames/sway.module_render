#ifndef SWAY_RENDER_SPRITE_DEBUG_HPP
#define SWAY_RENDER_SPRITE_DEBUG_HPP

// #include <sway/cmpt/component.hpp>
#include <sway/render/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/guides/axis.hpp>
#include <sway/render/rendercomponent.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Sprite_Debug : public RenderComponent {
  DECLARE_CLASS_METADATA(Sprite_Debug, RenderComponent)

public:
  Sprite_Debug() = default;

  ~Sprite_Debug();

  void initialize(
      RenderSubsystem::SharedPtr_t subsystem, RenderSubqueue::SharedPtr_t subqueue, Material::SharedPtr_t material);

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtm));

  [[nodiscard]]
  auto getMaterial() const -> Material::SharedPtr_t {
    return material_;
  }

private:
  Effect::Ptr_t effect_;
  RenderSubqueue::SharedPtr_t subqueue_;
  Material::SharedPtr_t material_;
  GeomBuilder::SharedPtr_t geomBuilder_;
  u32_t axisGeomIdx_;
  u32_t lineGeomIdx_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_SPRITE_DEBUG_HPP
