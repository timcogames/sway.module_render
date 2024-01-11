#include <sway/render/image.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Image::Image()
    : pluginFuncSet_(global::getGapiPluginFunctionSet()) {}

void Image::create(void *data, int width, int height) {
  texture_ = pluginFuncSet_->createTexture();
  texture_->create(data, width, height);

  textureSampler_ = pluginFuncSet_->createTextureSampler();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
