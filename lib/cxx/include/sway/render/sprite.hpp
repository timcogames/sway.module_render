#ifndef SWAY_RENDER_SPRITE_HPP
#define SWAY_RENDER_SPRITE_HPP

// #include <sway/cmpt/component.hpp>
#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/rendercomponent.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class Sprite : public RenderComponent {
  DECLARE_CLASS_METADATA(Sprite, RenderComponent)

public:
  using Ptr_t = Sprite *;
  using SharedPtr_t = std::shared_ptr<Sprite>;

#pragma region "Ctors/Dtor"

  Sprite() = default;

  ~Sprite();

#pragma endregion

  void initialize(RenderSubsystem::SharedPtr_t subsystem, RenderSubqueue::SharedPtr_t subqueue,
      Material::SharedPtr_t material, const math::size2f_t &size, const math::size2i_t &subdivs = math::size2i_t(1));

#pragma region "Override RenderComponent methods"

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtm));

#pragma endregion

  void updateGeometryUV(math::size2i_t textureSize, math::rect4f_t frameRect);

  [[nodiscard]]
  auto getMaterial() const -> Material::SharedPtr_t {
    return material_;
  }

  void setTexture(Image::Ptr texture, bool recomputeUVRequired);

  [[nodiscard]]
  auto getTexture() const -> Image::Ptr;

  void setTextureRect(const math::rect4i_t &rect);

  [[nodiscard]]
  auto getTextureRect() const -> math::rect4i_t;

  void recomputeUV();

private:
  RenderSubqueue::SharedPtr_t subqueue_;

  Material::SharedPtr_t material_;
  GeomBuilder::SharedPtr_t geomBuilder_;
  u32_t geomIdx_;

  Image::Ptr texture_;
  math::rect4i_t textureRect_;

  math::size2i_t subdivs_;

  // math::BoundingBox<2> boundingBox_;
  // std::vector<SpriteAnimation> animations_;
  // math::size2f_t sheetDims_;
  // math::size2f_t panelDims_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_SPRITE_HPP
