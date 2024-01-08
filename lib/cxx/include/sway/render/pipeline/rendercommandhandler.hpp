#ifndef SWAY_RENDER_PIPELINE_RENDERCOMMANDHANDLER_HPP
#define SWAY_RENDER_PIPELINE_RENDERCOMMANDHANDLER_HPP

#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(pipeline)

class RenderCommandHandler {
public:
  virtual ~RenderCommandHandler() = default;

  PURE_VIRTUAL(void execute(std::shared_ptr<RenderCommand> command));
};

NAMESPACE_END(pipeline)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PIPELINE_RENDERCOMMANDHANDLER_HPP
