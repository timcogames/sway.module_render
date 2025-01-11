#ifndef SWAY_RENDER_RENDERTARGET_HPP
#define SWAY_RENDER_RENDERTARGET_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/img/image.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class RenderTarget {
public:
#pragma region "Ctors/Dtor"

  RenderTarget() = default;

  DTOR_DEFAULT(RenderTarget);

#pragma endregion

  void setScissorViewport(gapi::typedefs::ViewportPtr_t viewport);

  void activate(gapi::typedefs::StateContextPtr_t ctx);

  void deactivate();

  void attachColorBufferObject(typedefs::RenderSubsystemPtr_t subsys);

  auto getColorBuffer() const -> ImageTypedefs::SharedPtr_t { return colorTex_; }

private:
  gapi::typedefs::ViewportPtr_t viewport_;
  gapi::typedefs::FrameBufferPtr_t colorFBO_;
  gapi::typedefs::RenderBufferPtr_t renderBO_;
  ImageTypedefs::SharedPtr_t colorTex_;
  bool attached_{false};
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERTARGET_HPP
