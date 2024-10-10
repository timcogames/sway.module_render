#include <sway/render/global.hpp>
#include <sway/render/rendersubsystem.hpp>
#include <sway/render/rendertarget.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

void RenderTarget::setScissorViewport(gapi::ViewportPtr_t viewport) { viewport_ = viewport; }

void RenderTarget::attachColorBufferObject(RenderSubsystemPtr_t subsys) {
  attached_ = true;

  i32_t wdt = 800;
  i32_t hgt = 600;
  // u32_t depth = 4;
  // s8_t *texdata = new s8_t[depth * wdt * hgt];

  // for (auto y = 0; y < hgt; ++y) {
  //   for (auto x = 0; x < wdt; ++x) {
  //     i32_t c = (((y & 0x8) == 0) ^ ((x & 0x8)) == 0) * 255;

  //     texdata[y * wdt * depth + x * depth + 0] = c;  // red
  //     texdata[y * wdt * depth + x * depth + 1] = c;  // green
  //     texdata[y * wdt * depth + x * depth + 2] = c;  // blue
  //     texdata[y * wdt * depth + x * depth + 3] = 255;  // alpha
  //   }
  // }

  gapi::TextureCreateInfo colorTexCreateInfo;
  colorTexCreateInfo.target = gapi::TextureTarget::Enum::TEX_2D;
  colorTexCreateInfo.size = math::sizei_t(wdt, hgt);
  colorTexCreateInfo.format = gapi::PixelFormat::RGBA;
  colorTexCreateInfo.internalFormat = gapi::PixelFormat::RGBA8;
  colorTexCreateInfo.dataType = core::ValueDataType::Enum::UBYTE;
  colorTexCreateInfo.pixels = (s8_t *)nullptr;
  colorTexCreateInfo.mipLevels = 0;

  // SAFE_DELETE_ARRAY(texdata);

  colorTex_ = std::make_shared<Image>();
  colorTex_->create(subsys->textureIdGenerator_, colorTexCreateInfo);
  colorTex_->getTextureSampler()->setWrapMode(
      gapi::TextureWrap::Enum::CLAMP, gapi::TextureWrap::Enum::CLAMP, gapi::TextureWrap::Enum::CLAMP);
  colorTex_->getTextureSampler()->setFilterMode(gapi::TextureFilter::Enum::LINEAR, gapi::TextureFilter::Enum::LINEAR);

  colorFBO_ = global::getGapiPluginFunctionSet()->createFrameBuffer(subsys->frameBufferIdGenerator_);
  colorFBO_->bind();
  colorFBO_->attach(gapi::FramebufferAttachment::Enum::COL_1, colorTex_->getTexture(), 0);

  // renderBO_ = global::getGapiPluginFunctionSet()->createRenderBuffer();
  // renderBO_->bind();
  // renderBO_->store(gapi::PixelFormat::D24S8, math::size2i_t(800, 600), 0);

  // colorFBO_->attach(gapi::FramebufferAttachment::Enum::DEPTH_STENCIL, renderBO_);
}

void RenderTarget::activate(gapi::StateContextPtr_t ctx) {
  // if (attached_) {
  colorFBO_->bind();

  u32_t DrawBuffers[2] = {0x8CE0, 0x0};
  colorFBO_->drawBuffers(2, DrawBuffers);
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
