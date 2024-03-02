#ifndef SWAY_RENDER_IMAGE_HPP
#define SWAY_RENDER_IMAGE_HPP

#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render/global.hpp>
#include <sway/render/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class Image {
public:
  Image();

  ~Image() = default;

  void create(void *data, math::size2i_t size);

  void create(const gapi::TextureCreateInfo &createInfo);

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

private:
  global::GapiPluginFunctionSet *pluginFuncSet_;
  gapi::TexturePtr_t texture_;  // Указатель на шейдерную программу.
  gapi::TextureSamplerPtr_t textureSampler_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_IMAGE_HPP
