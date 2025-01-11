#ifndef SWAY_RENDER_IMAGE_HPP
#define SWAY_RENDER_IMAGE_HPP

#include <sway/render/global.hpp>
#include <sway/render/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Image {
public:
#pragma region "Ctors/Dtor"

  Image();

  DTOR_DEFAULT(Image);

#pragma endregion

#pragma region "Creating/Destroying"

  void create(gapi::typedefs::IdGeneratorPtr_t idgen, const gapi::TextureCreateInfo &createInfo);

  void create(gapi::typedefs::IdGeneratorPtr_t idgen, const loader::ImageDescriptor &desc);

#pragma endregion

#pragma region "Binding/Unbinding"

  /**
   * \~english @brief Binds the image to the graphics pipeline.
   * \~russian @brief Связывает изображение с графическим конвейером.
   */
  void bind() { texture_->bind(); }

  /**
   * \~english @brief Unbind.
   * \~russian @brief Отвязывает.
   */
  void unbind() { texture_->unbind(); }

#pragma endregion

#pragma region "Getters/Setters"

  auto getTexture() -> gapi::typedefs::TexturePtr_t { return texture_; }

  auto getTextureSampler() -> gapi::typedefs::TextureSamplerPtr_t { return textureSampler_; }

  [[nodiscard]] auto getSize() const -> math::size2i_t { return textureCreateInfo_.size; }

#pragma endregion

private:
  global::GapiPluginFunctionSet *pluginFuncSet_;
  gapi::TextureCreateInfo textureCreateInfo_;
  gapi::typedefs::TexturePtr_t texture_;
  gapi::typedefs::TextureSamplerPtr_t textureSampler_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_IMAGE_HPP
