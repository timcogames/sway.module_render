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

  void setScissorViewport(std::shared_ptr<gapi::Viewport> viewport);

  void activate();

  void deactivate();

private:
  std::shared_ptr<gapi::Viewport> viewport_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERTARGET_HPP
