#ifndef SWAY_RENDER_RENDERTARGET_HPP
#define SWAY_RENDER_RENDERTARGET_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/image.hpp>
#include <sway/render/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderTarget {
  DECLARE_CLASS_POINTER_ALIASES(RenderTarget)

public:
#pragma region "Ctors/Dtor"

  RenderTarget() = default;

  ~RenderTarget() = default;

#pragma endregion

  void setScissorViewport(gapi::ViewportPtr_t viewport);

  void activate(gapi::StateContextPtr_t ctx);

  void deactivate();

  void attachColorBufferObject();

  auto getColorBuffer() const -> Image::SharedPtr_t { return colorTex_; }

private:
  gapi::ViewportPtr_t viewport_;
  gapi::Framebuffer::Ptr_t colorFBO_;
  gapi::RenderBuffer::Ptr_t renderBO_;
  Image::SharedPtr_t colorTex_;
  bool attached_{false};
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERTARGET_HPP
