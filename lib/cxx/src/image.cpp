#include <sway/render/image.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Image::Image()
    : pluginFuncSet_(global::getGapiPluginFunctionSet()) {}

void Image::create(void *data, math::size2i_t size) {
  gapi::TextureCreateInfo createInfo;
  createInfo.target = gapi::TextureTarget::TEX_2D;
  createInfo.size = size;
  // createInfo.arraySize
  createInfo.format = gapi::PixelFormat::RGBA;
  createInfo.internalFormat = gapi::PixelFormat::RGBA;
  createInfo.dataType = core::ValueDataType::UBYTE;
  createInfo.pixels = (s8_t *)data;
  createInfo.mipLevels = 0;
  // createInfo.sampleCount

  texture_ = pluginFuncSet_->createTexture(createInfo);
  textureSampler_ = pluginFuncSet_->createTextureSampler(texture_);
}

void Image::create(const gapi::TextureCreateInfo &createInfo) {
  texture_ = pluginFuncSet_->createTexture(createInfo);
  textureSampler_ = pluginFuncSet_->createTextureSampler(texture_);
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
