#ifndef SWAY_RENDER_RENDERQUEUEPASS_HPP
#define SWAY_RENDER_RENDERQUEUEPASS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderpass.hpp>
#include <sway/render/renderqueue.hpp>

#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class RenderQueuePass : public RenderQueue, public RenderPass {
  DECLARE_CLASS_POINTER_ALIASES(RenderQueuePass)

public:
  RenderQueuePass(const std::string &name);

  virtual ~RenderQueuePass() = default;

  MTHD_OVERRIDE(void apply(gapi::Framebuffer::Ptr_t framebuf));

  MTHD_OVERRIDE(void execute());
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERQUEUEPASS_HPP
