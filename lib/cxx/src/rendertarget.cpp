#include <sway/render/global.hpp>
#include <sway/render/rendertarget.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

void RenderTarget::setScissorViewport(gapi::ViewportPtr_t viewport) { viewport_ = viewport; }

void RenderTarget::attachColorBufferObject() {
  attached_ = true;

  gapi::TextureCreateInfo colorTexCreateInfo;
  colorTexCreateInfo.target = gapi::TextureTarget::TEX_2D;
  colorTexCreateInfo.size = math::sizei_t(800, 600);
  colorTexCreateInfo.format = gapi::PixelFormat::RGB;
  colorTexCreateInfo.internalFormat = gapi::PixelFormat::RGB;
  colorTexCreateInfo.dataType = core::ValueDataType::UBYTE;
  colorTexCreateInfo.pixels = (s8_t *)nullptr;
  colorTexCreateInfo.mipLevels = 0;

  colorTex_ = std::make_shared<Image>();
  colorTex_->create(colorTexCreateInfo);
  colorTex_->getTextureSampler()->setWrapMode(
      gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT);
  colorTex_->getTextureSampler()->setFilterMode(gapi::TextureFilter::NEAREST, gapi::TextureFilter::NEAREST);

  colorFbo_ = global::getGapiPluginFunctionSet()->createFramebuffer();
  colorFbo_->attach(gapi::FramebufferAttachment::COL_1, colorTex_->getTexture(), 0);
}

void RenderTarget::activate() {
  if (attached_) {
    colorFbo_->bind();
  }

  viewport_->setClearColor(math::col4f_t(50.0F, 50.0F, 50.0F, 1.0F));
  // viewport_->clear(gapi::ClearFlag::COLOR | gapi::ClearFlag::DEPTH | gapi::ClearFlag::STENCIL);

  if (attached_) {
    viewport_->clear(gapi::ClearFlag::COLOR);
  } else {
    viewport_->clear(gapi::ClearFlag::NONE);
  }
}

void RenderTarget::deactivate() {
  if (attached_) {
    colorFbo_->unbind();
  }
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
