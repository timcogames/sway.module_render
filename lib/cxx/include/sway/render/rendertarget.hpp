#ifndef SWAY_RENDER_RENDERTARGET_HPP
#define SWAY_RENDER_RENDERTARGET_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/img/image.hpp>

namespace sway::render {

class RenderTarget {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  RenderTarget() = default;

  ~RenderTarget() = default;

  /** @} */
#pragma endregion

  void setScissorViewport(gapi::typedefs::ViewportPtr_t viewport);

  void activate(gapi::typedefs::StateContextPtr_t ctx);

  void deactivate();

  void attachColorBufferObject(RenderSubsystemPtr_t subsys);

  auto getColorBuffer() const -> ImageTypedefs::SharedPtr_t { return colorTex_; }

private:
  gapi::typedefs::ViewportPtr_t viewport_;
  gapi::typedefs::FrameBufferPtr_t colorFBO_;
  gapi::typedefs::RenderBufferPtr_t renderBO_;
  ImageTypedefs::SharedPtr_t colorTex_;
  bool attached_{false};
};

}  // namespace sway::render

#endif  // SWAY_RENDER_RENDERTARGET_HPP
