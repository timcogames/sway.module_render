#ifndef SWAY_RENDER_SPRITE_HPP
#define SWAY_RENDER_SPRITE_HPP

// #include <sway/cmpt/component.hpp>
#include <sway/render/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/guides/axis.hpp>
#include <sway/render/procedurals/prims/plane.hpp>
#include <sway/render/rendercomponent.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class Sprite : public RenderComponent {
public:
  DECLARE_CLASS_METADATA(Sprite, RenderComponent)

  Sprite() = default;

  ~Sprite() = default;

  void initialize(std::shared_ptr<RenderSubsystem> subsystem, std::shared_ptr<RenderSubqueue> subqueue,
      std::shared_ptr<Material> material, const math::size2f_t &size);

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t transform, math::mat4f_t proj, math::mat4f_t view, f32_t deltaTime));

  void updateGeometryUV(math::size2f_t textureSize, math::rect4f_t frameRect);

  [[nodiscard]] auto getMaterial() const -> std::shared_ptr<Material> { return material_; }

private:
  RenderSubqueueRef_t subqueue_;
  std::shared_ptr<Effect> effect_;
  std::shared_ptr<Material> material_;
  std::shared_ptr<Geometry> geometry_;

  // math::BoundingBox<2> boundingBox_;
  // std::vector<SpriteAnimation> animations_;
  // math::size2f_t sheetDims_;
  // math::size2f_t panelDims_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_SPRITE_HPP
