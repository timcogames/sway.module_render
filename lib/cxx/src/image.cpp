#include <sway/render/image.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Image::Image()
    : pluginFuncSet_(global::getGapiPluginFunctionSet())
    , texture_(nullptr)
    , textureSampler_(nullptr) {}

void Image::create(const gapi::TextureCreateInfo &createInfo) {
  texture_ = pluginFuncSet_->createTexture(createInfo);
  textureSampler_ = pluginFuncSet_->createTextureSampler(texture_);
}

void Image::create(const loader::ImageDescriptor &desc) {
  textureCreateInfo_.target = gapi::TextureTarget::TEX_2D;
  textureCreateInfo_.size = desc.size;
  // textureCreateInfo_.arraySize
  textureCreateInfo_.format = gapi::PixelFormat::RGBA;
  textureCreateInfo_.internalFormat = gapi::PixelFormat::RGBA;
  textureCreateInfo_.dataType = core::ValueDataType::UBYTE;
  textureCreateInfo_.pixels = (s8_t *)desc.buf.data;
  textureCreateInfo_.mipLevels = 0;
  // createInfo.sampleCount

  this->create(textureCreateInfo_);
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
