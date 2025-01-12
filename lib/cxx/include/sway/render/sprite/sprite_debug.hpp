#ifndef SWAY_RENDER_SPRITE_DEBUG_HPP
#define SWAY_RENDER_SPRITE_DEBUG_HPP

// #include <sway/cmpt/component.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/mtrl/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/procedurals/guides/axis.hpp>
#include <sway/render/rendercomponent.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>

namespace sway::render {

class Sprite_Debug : public RenderComponent {
  DECLARE_CLASS_METADATA(Sprite_Debug, RenderComponent)

public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Sprite_Debug() = default;

  DTOR(Sprite_Debug);

  /** @} */
#pragma endregion

  void initialize(
      RenderSubsystemSharedPtr_t subsystem, RenderSubqueueSharedPtr_t subqueue, MaterialTypedefs::SharedPtr_t material);

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtm));

  [[nodiscard]] auto getMaterial() const -> MaterialTypedefs::SharedPtr_t { return material_; }

private:
  EffectTypedefs::Ptr_t effect_;
  RenderSubqueueSharedPtr_t subqueue_;
  MaterialTypedefs::SharedPtr_t material_;
  GeomBuilderTypedefs::SharedPtr_t geomBuilder_;
  u32_t axisGeomIdx_;
  u32_t lineGeomIdx_;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_SPRITE_DEBUG_HPP
