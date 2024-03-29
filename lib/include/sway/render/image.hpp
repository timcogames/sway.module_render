#ifndef SWAY_RENDER_IMAGE_HPP
#define SWAY_RENDER_IMAGE_HPP

#include <sway/render/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class Image {
public:
  Image(void *data, int width, int height);

  ~Image() = default;

  /**
   * @brief Привязывает.
   */
  void bind() { texture_->bind(); }

  /**
   * @brief Отвязывает.
   */
  void unbind() { texture_->unbind(); }

  auto getTexture() -> gapi::TextureRef_t { return texture_; }

  auto getTextureSampler() -> gapi::TextureSamplerRef_t { return textureSampler_; }

private:
  gapi::TextureRef_t texture_;  // Указатель на шейдерную программу.
  gapi::TextureSamplerRef_t textureSampler_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_IMAGE_HPP
