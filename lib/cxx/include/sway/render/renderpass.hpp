#ifndef SWAY_RENDER_RENDERPASS_HPP
#define SWAY_RENDER_RENDERPASS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/renderstate.hpp>
#include <sway/render/rendertarget.hpp>
#include <sway/render/temp/pipeline/stage/pass/passtypes.hpp>

#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class RenderPass {
  DECLARE_PTR_ALIASES(RenderPass)
  DECLARE_PTR_VECTOR(RenderPass, SharedPtr)

public:
  RenderPass(const std::string &name, PassType::Enum type)
      : name_(name)
      , type_(type) {}

  DTOR_VIRTUAL_DEFAULT(RenderPass);

  PURE_VIRTUAL(void setup());

  PURE_VIRTUAL(void dispose());

  PURE_VIRTUAL(void apply(gapi::FrameBuffer::Ptr_t framebuf));

  PURE_VIRTUAL(void execute());

  // PURE_VIRTUAL(void apply(FrameBuffer &framebuf, const RenderMetaData &metadata));

  // PURE_VIRTUAL(void apply(gapi::FrameBuffer::SharedPtr_t src, gapi::FrameBuffer::SharedPtr_t dst));

  auto name() const -> const std::string & { return name_; }

  auto type() const -> PassType::Enum { return type_; }

private:
  std::string name_;
  PassType::Enum type_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERPASS_HPP
