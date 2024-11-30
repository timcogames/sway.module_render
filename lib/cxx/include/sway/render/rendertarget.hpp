#ifndef SWAY_RENDER_RENDERTARGET_HPP
#define SWAY_RENDER_RENDERTARGET_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/img/image.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class RenderTarget {
  DECLARE_PTR_ALIASES(RenderTarget)

public:
#pragma region "Ctors/Dtor"

  RenderTarget() = default;

  DTOR_DEFAULT(RenderTarget);

#pragma endregion

  void setScissorViewport(gapi::ViewportPtr_t viewport);

  void activate(gapi::StateContextPtr_t ctx);

  void deactivate();

  void attachColorBufferObject(RenderSubsystemPtr_t subsys);

  auto getColorBuffer() const -> ImageTypedefs::SharedPtr_t { return colorTex_; }

private:
  gapi::ViewportPtr_t viewport_;
  gapi::FrameBuffer::Ptr_t colorFBO_;
  gapi::RenderBuffer::Ptr_t renderBO_;
  ImageTypedefs::SharedPtr_t colorTex_;
  bool attached_{false};
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERTARGET_HPP
