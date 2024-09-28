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

  colorFBO_ = global::getGapiPluginFunctionSet()->createFramebuffer();
  colorFBO_->attach(gapi::FramebufferAttachment::COL_1, colorTex_->getTexture(), 0);

  renderBO_ = global::getGapiPluginFunctionSet()->createRenderBuffer();
  renderBO_->store(gapi::PixelFormat::RGBA4, math::size2i_t(800, 600), 0);
}

void RenderTarget::activate(gapi::StateContextPtr_t ctx) {
  auto clearFlags = core::detail::toBase(gapi::ClearFlag::COLOR);

  if (attached_) {
    colorFBO_->bind();
  }

  if (clearFlags & core::detail::toBase(gapi::ClearFlag::COLOR)) {
    viewport_->setClearColor(math::col4f_t(50.0F, 50.0F, 50.0F, 1.0F));
  }

  auto clearDepth = 0;
  if (clearFlags & core::detail::toBase(gapi::ClearFlag::DEPTH)) {
    ctx->setClearDepth(clearDepth);
    ctx->setDepthMask(true);
  }

  auto clearStencil = 0;
  if (clearFlags & core::detail::toBase(gapi::ClearFlag::STENCIL)) {
    ctx->setClearStencil(clearStencil);
    ctx->setStencilMask(0x0);
  }

  viewport_->clear(core::detail::toEnum<gapi::ClearFlag>(clearFlags));
}

void RenderTarget::deactivate() {
  if (attached_) {
    colorFBO_->unbind();
  }
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
