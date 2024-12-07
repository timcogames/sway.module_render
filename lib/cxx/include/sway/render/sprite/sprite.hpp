#ifndef SWAY_RENDER_SPRITE_HPP
#define SWAY_RENDER_SPRITE_HPP

// #include <sway/cmpt/component.hpp>
#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/mtrl/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/rendercomponent.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Sprite : public RenderComponent {
  DECLARE_CLASS_METADATA(Sprite, RenderComponent)
  DECLARE_PTR_ALIASES(Sprite)

public:
#pragma region "Ctors/Dtor"

  Sprite() = default;

  DTOR(Sprite);

#pragma endregion

  void initialize(RenderSubsystem::SharedPtr_t subsys, RenderSubqueue::SharedPtr_t subqueue,
      MaterialTypedefs::SharedPtr_t material, const math::size2f_t &size,
      const math::size2i_t &subdivs = math::size2i_t(1));

#pragma region "Overridden RenderComponent methods"

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtm));

#pragma endregion

  void updateGeometryUV(math::size2i_t textureSize, math::rect4f_t frameRect);

  void recomputeUV();

#pragma region "Getters/Setters"

  [[nodiscard]] auto getMaterial() const -> MaterialTypedefs::SharedPtr_t { return material_; }

  void setTexture(ImageTypedefs::SharedPtr_t texture, bool recomputeUVRequired);

  [[nodiscard]] auto getTexture() const -> ImageTypedefs::SharedPtr_t;

  void setTextureRect(const math::rect4i_t &rect);

  [[nodiscard]] auto getTextureRect() const -> math::rect4i_t;

#pragma endregion

  // void setFlippedX(bool flippedX) {
  //   if (flippedX_ != flippedX) {
  //     textureRect_.x += textureRect_.w;
  //     textureRect_.w *= -1;
  //     flippedX_ = flippedX;

  //     dirtyBits_.set(DirtyBitPosition::TEXTURE_BIT);
  //   }
  // }

  // void setFlippedY(bool flippedY) {
  //   if (flippedY_ != flippedY) {
  //     textureRect_.y += textureRect_.h;
  //     textureRect_.h *= -1;
  //     flippedY_ = flippedY;

  //     dirtyBits_.set(DirtyBitPosition::TEXTURE_BIT);
  //   }
  // }

private:
  RenderSubqueue::SharedPtr_t subqueue_;

  MaterialTypedefs::SharedPtr_t material_;
  GeomBuilder::SharedPtr_t geomBuilder_;
  u32_t geomIdx_;

  ImageTypedefs::SharedPtr_t texture_;
  math::rect4i_t textureRect_;

  math::size2i_t subdivs_;

  // math::BoundingBox<2> boundingBox_;
  // std::vector<SpriteAnimation> animations_;
  // math::size2f_t sheetDims_;
  // math::size2f_t panelDims_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_SPRITE_HPP
