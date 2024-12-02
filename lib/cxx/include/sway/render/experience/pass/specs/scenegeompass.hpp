#ifndef SWAY_RENDER_EXPERIENCE_SCENEGEOMPASS_HPP
#define SWAY_RENDER_EXPERIENCE_SCENEGEOMPASS_HPP

#include <sway/render/experience/pass/specs/graphicspass.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class SceneGeomPass : public GraphicsPass {
public:
#pragma region "Ctors/Dtor"

  SceneGeomPass(const PassDescriptor &desc)
      : GraphicsPass(desc) {}

  DTOR_VIRTUAL_DEFAULT(SceneGeomPass);

#pragma endregion

  void setup() {
    auto &executor = this->getQueue()->getExecutor();
    executor.registerHandler(std::make_unique<BeginPassCommandHandler>());
    executor.registerHandler(std::make_unique<EndPassCommandHandler>());
    executor.registerHandler(std::make_unique<DrawCommandHandler>());

    commandBufferOpt_ = this->getQueue()->createBuffer((struct CommandBufferDescriptor){.group = 0, .priority = 0});
  }

  void render() {
    if (!commandBufferOpt_.has_value()) {
      return;
    }

    auto &buf = commandBufferOpt_->get();
    buf.enqueue(std::make_unique<BeginPassCommand>(*this));
    buf.enqueue(std::make_unique<DrawCommand>());
    buf.enqueue(std::make_unique<EndPassCommand>());

    GraphicsPass::render();
  }

private:
  CommandBufferTypedefs::OptionalRef_t commandBufferOpt_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_SCENEGEOMPASS_HPP
