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

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Sprite : public RenderComponent {
  DECLARE_CLASS_METADATA(Sprite, RenderComponent)
  DECLARE_CLASS_POINTER_ALIASES(Sprite)

public:
#pragma region "Ctors/Dtor"

  Sprite() = default;

  ~Sprite();

#pragma endregion

  void initialize(RenderSubsystem::SharedPtr_t subsys, RenderSubqueue::SharedPtr_t subqueue,
      Material::SharedPtr_t material, const math::size2f_t &size, const math::size2i_t &subdivs = math::size2i_t(1));

#pragma region "Override RenderComponent methods"

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtm));

#pragma endregion

  void updateGeometryUV(math::size2i_t textureSize, math::rect4f_t frameRect);

  [[nodiscard]]
  auto getMaterial() const -> Material::SharedPtr_t {
    return material_;
  }

  void setTexture(Image::SharedPtr_t texture, bool recomputeUVRequired);

  [[nodiscard]]
  auto getTexture() const -> Image::SharedPtr_t;

  void setTextureRect(const math::rect4i_t &rect);

  [[nodiscard]]
  auto getTextureRect() const -> math::rect4i_t;

  void recomputeUV();

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

  Material::SharedPtr_t material_;
  GeomBuilder::SharedPtr_t geomBuilder_;
  u32_t geomIdx_;

  Image::SharedPtr_t texture_;
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
