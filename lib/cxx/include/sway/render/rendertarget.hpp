#ifndef SWAY_RENDER_RENDERTARGET_HPP
#define SWAY_RENDER_RENDERTARGET_HPP

#include <sway/gapi.hpp>
#include <sway/namespacemacros.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class RenderTarget {
public:
  RenderTarget() = default;

  ~RenderTarget() = default;

  void setScissorViewport(gapi::ViewportPtr_t viewport);

  void activate();

  void deactivate();

private:
  gapi::ViewportPtr_t viewport_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERTARGET_HPP
