
#include <sway/render/experience/renderer/renderer.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

Renderer::Renderer(u32_t type)
    : type_(type) {
  commandQueue_ = std::make_unique<CommandQueue>();
  registerCommandHandlers_();
}

void Renderer::registerCommandHandlers_() {
  auto &executor = commandQueue_->getExecutor();
  executor.registerHandler(std::make_unique<BindPipelineCommandHandler>());
  executor.registerHandler(std::make_unique<BeginPassCommandHandler>());
  executor.registerHandler(std::make_unique<ClearCommandHandler>());
  executor.registerHandler(std::make_unique<DrawCommandHandler>());
  executor.registerHandler(std::make_unique<EndPassCommandHandler>());
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
