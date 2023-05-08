#include <sway/render/global.hpp>
#include <sway/render/image.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Image::Image(void *data, int width, int height) {
  auto *pluginFuncSet = global::getGapiFunctionSet();

  texture_ = pluginFuncSet->createTexture();
  texture_->create(data, width, height);

  textureSampler_ = pluginFuncSet->createTextureSampler();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
