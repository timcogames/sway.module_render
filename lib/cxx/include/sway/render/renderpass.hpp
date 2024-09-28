#ifndef SWAY_RENDER_RENDERPASS_HPP
#define SWAY_RENDER_RENDERPASS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderstate.hpp>
#include <sway/render/rendertarget.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

// enum class RenderPassType : u32_t { DEPTH, COLOR, REFRACT, BLENDED, SENTINEL };
// enum class RenderPassAction { KEEP = 0, CLEAR = 1, DONT_CARE = 2 };

// struct RenderPassInfo {
//   RenderPassAction color;
//   RenderPassAction depth;
//   RenderPassAction stencil;
//   u32_t clearColor;
//   u32_t clearDepth;
//   u32_t clearStencil;
// };

class RenderPass {
  DECLARE_CLASS_POINTER_ALIASES(RenderPass)

public:
  RenderPass(const std::string &name)
      : name_(name) {}

  virtual ~RenderPass() = default;

  PURE_VIRTUAL(void apply(gapi::Framebuffer::Ptr_t framebuf));

  // PURE_VIRTUAL(void apply(FrameBuffer &framebuf, const RenderMetaData &metadata));

  // PURE_VIRTUAL(void apply(gapi::FrameBuffer::SharedPtr_t src, gapi::FrameBuffer::SharedPtr_t dst));

  auto name() const -> const std::string & { return name_; }

private:
  // u32_t id_;
  std::string name_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_RENDERPASS_HPP
