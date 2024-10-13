#include <sway/render/global.hpp>
#include <sway/render/rendersubsystem.hpp>
#include <sway/render/rendertarget.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

void RenderTarget::setScissorViewport(gapi::ViewportPtr_t viewport) { viewport_ = viewport; }

void RenderTarget::attachColorBufferObject(RenderSubsystemPtr_t subsys) {
  attached_ = true;

  auto texSize = math::sizei_t(800, 600);

  gapi::TextureCreateInfo texCreateInfo;
  texCreateInfo.target = gapi::TextureTarget::Enum::TEX_2D;
  texCreateInfo.size = texSize;
  texCreateInfo.format = gapi::PixelFormat::RGBA;
  texCreateInfo.internalFormat = gapi::PixelFormat::RGBA8;
  texCreateInfo.dataType = core::ValueDataType::Enum::UBYTE;
  texCreateInfo.pixels = (s8_t *)nullptr;
  texCreateInfo.mipLevels = 0;

  colorTex_ = std::make_shared<Image>();
  colorTex_->create(subsys->textureIdGenerator_, texCreateInfo);
  colorTex_->getTextureSampler()->setWrapMode(
      gapi::TextureWrap::Enum::CLAMP, gapi::TextureWrap::Enum::CLAMP, gapi::TextureWrap::Enum::CLAMP);
  colorTex_->getTextureSampler()->setFilterMode(gapi::TextureFilter::Enum::LINEAR, gapi::TextureFilter::Enum::LINEAR);

  colorFBO_ = global::getGapiPluginFunctionSet()->createFrameBuffer(subsys->frameBufferIdGenerator_);
  colorFBO_->bind();
  colorFBO_->attach(gapi::FrameBufferAttachment::Enum::COL_1, colorTex_->getTexture(), 0);

  renderBO_ = global::getGapiPluginFunctionSet()->createRenderBuffer();
  renderBO_->bind();
  renderBO_->store(gapi::PixelFormat::D24S8, texSize, 0);

  colorFBO_->attach(gapi::FrameBufferAttachment::Enum::DEPTH_STENCIL, renderBO_);
}

void RenderTarget::activate(gapi::StateContextPtr_t ctx) {
  // if (attached_) {
  colorFBO_->bind();

  // u32_t DrawBuffers[2] = {0x8CE0, 0x0};
  // colorFBO_->drawBuffers(2, DrawBuffers);

  // std::vector<u32_t> buffers = {0x0};
  // colorFBO_->drawBuffers(1, buffers.data());
  // }

  // auto clearFlags = core::detail::toBase(gapi::ClearFlag::COLOR) | core::detail::toBase(gapi::ClearFlag::DEPTH);

  // if (clearFlags & core::detail::toBase(gapi::ClearFlag::COLOR)) {
  // viewport_->setClearColor(math::col4f_t(50.0F, 50.0F, 50.0F, 1.0F));
  // }

  // auto clearDepth = 0;
  // if (clearFlags & core::detail::toBase(gapi::ClearFlag::DEPTH)) {
  //   ctx->setClearDepth(clearDepth);
  //   ctx->setDepthMask(true);
  // }

  // auto clearStencil = 0;
  // if (clearFlags & core::detail::toBase(gapi::ClearFlag::STENCIL)) {
  //   ctx->setClearStencil(clearStencil);
  //   ctx->setStencilMask(0x0);
  // }

  // viewport_->clear(core::detail::toEnum<gapi::ClearFlag>(clearFlags));
}

void RenderTarget::deactivate() {
  // if (attached_) {
  colorFBO_->unbind();
  // }
}

NS_END()  // namespace render
NS_END()  // namespace sway
