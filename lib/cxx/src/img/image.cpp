#include <sway/render/img/image.hpp>
#include <sway/render/rendersubsystem.hpp>

namespace sway::render {

Image::Image()
    : pluginFuncSet_(global::getGapiPluginFunctionSet())
    , texture_(nullptr)
    , textureSampler_(nullptr) {}

void Image::create(gapi::typedefs::IdGeneratorPtr_t idgen, const gapi::TextureCreateInfo &createInfo) {
  texture_ = pluginFuncSet_->createTexture(idgen, createInfo);
  textureSampler_ = pluginFuncSet_->createTextureSampler(texture_);
}

void Image::create(gapi::typedefs::IdGeneratorPtr_t idgen, const loader::ImageDescriptor &desc) {
  textureCreateInfo_.target = gapi::TextureTarget::Enum::TEX_2D;
  textureCreateInfo_.size = desc.size;
  // textureCreateInfo_.arraySize
  textureCreateInfo_.format = gapi::PixelFormat::RGBA;
  textureCreateInfo_.internalFormat = gapi::PixelFormat::RGBA;
  textureCreateInfo_.dataType = core::ValueDataType::Enum::UBYTE;

#ifdef EMSCRIPTEN_PLATFORM
  emscripten::val data = desc.buf.data;
  size_t len = data["length"].as<size_t>();
  s8_t *pixels = static_cast<s8_t *>(malloc(len));
  emscripten::val view = emscripten::val(emscripten::typed_memory_view(len, reinterpret_cast<uint8_t *>(pixels)));
  view.call<void>("set", data);
  textureCreateInfo_.pixels = pixels;
  free(pixels);
#else
  textureCreateInfo_.pixels = (s8_t *)desc.buf.data;
#endif

  textureCreateInfo_.mipLevels = 0;
  // createInfo.sampleCount

  create(idgen, textureCreateInfo_);
}

}  // namespace sway::render
