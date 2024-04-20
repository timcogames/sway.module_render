#ifndef SWAY_RENDER_IMAGE_HPP
#define SWAY_RENDER_IMAGE_HPP

#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/global.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/rms.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class Image {
public:
  using Ptr = std::shared_ptr<Image>;

  Image();

  ~Image() = default;

  void create(const gapi::TextureCreateInfo &createInfo);

  void create(const loader::ImageDescriptor &desc);

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

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_IMAGE_HPP
