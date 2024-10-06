#include <sway/render/image.hpp>
#include <sway/render/rendersubsystem.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

Image::Image()
    : pluginFuncSet_(global::getGapiPluginFunctionSet())
    , texture_(nullptr)
    , textureSampler_(nullptr) {}

void Image::create(gapi::IdGenerator::Ptr_t idgen, const gapi::TextureCreateInfo &createInfo) {
  texture_ = pluginFuncSet_->createTexture(idgen, createInfo);
  textureSampler_ = pluginFuncSet_->createTextureSampler(texture_);
}

void Image::create(gapi::IdGenerator::Ptr_t idgen, const loader::ImageDescriptor &desc) {
  textureCreateInfo_.target = gapi::TextureTarget::Enum::TEX_2D;
  textureCreateInfo_.size = desc.size;
  // textureCreateInfo_.arraySize
  textureCreateInfo_.format = gapi::PixelFormat::RGBA;
  textureCreateInfo_.internalFormat = gapi::PixelFormat::RGBA;
  textureCreateInfo_.dataType = core::ValueDataType::Enum::UBYTE;
  textureCreateInfo_.pixels = (s8_t *)desc.buf.data;
  textureCreateInfo_.mipLevels = 0;
  // createInfo.sampleCount

  create(idgen, textureCreateInfo_);
}

NS_END()  // namespace render
NS_END()  // namespace sway
