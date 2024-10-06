#ifndef SWAY_RENDER_PIPELINE_RENDERCOMMANDHANDLER_HPP
#define SWAY_RENDER_PIPELINE_RENDERCOMMANDHANDLER_HPP

#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(pipeline)

class RenderCommandHandler {
public:
  virtual ~RenderCommandHandler() = default;

  PURE_VIRTUAL(void execute(std::shared_ptr<RenderCommand> command));
};

NS_END()  // namespace pipeline
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PIPELINE_RENDERCOMMANDHANDLER_HPP
