#ifndef SWAY_RENDER_IMAGE_HPP
#define SWAY_RENDER_IMAGE_HPP

#include <sway/render/global.hpp>
#include <sway/render/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Image {
  DECLARE_CLASS_POINTER_ALIASES(Image)

public:
  Image();

  ~Image() = default;

  void create(gapi::IdGenerator::Ptr_t idgen, const gapi::TextureCreateInfo &createInfo);

  void create(gapi::IdGenerator::Ptr_t idgen, const loader::ImageDescriptor &desc);

  /**
   * @brief Привязывает.
   */
  void bind() { texture_->bind(); }

  /**
   * @brief Отвязывает.
   */
  void unbind() { texture_->unbind(); }

  auto getTexture() -> gapi::TexturePtr_t { return texture_; }

  auto getTextureSampler() -> gapi::TextureSamplerPtr_t { return textureSampler_; }

  [[nodiscard]]
  auto getSize() const -> math::size2i_t {
    return textureCreateInfo_.size;
  }

private:
  global::GapiPluginFunctionSet *pluginFuncSet_;
  gapi::TextureCreateInfo textureCreateInfo_;
  gapi::TexturePtr_t texture_;
  gapi::TextureSamplerPtr_t textureSampler_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_IMAGE_HPP
