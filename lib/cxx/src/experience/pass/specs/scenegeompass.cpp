#include <sway/render/experience/command/specs/beginpasscommand.hpp>
#include <sway/render/experience/command/specs/drawcommand.hpp>
#include <sway/render/experience/command/specs/endpasscommand.hpp>
#include <sway/render/experience/pass/specs/scenegeompass.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

SceneGeomPass::SceneGeomPass(const PassDescriptor &desc)
    : GraphicsPass(desc) {}

void SceneGeomPass::setup() {
  bufferOpt_ = this->getQueue()->createBuffer((struct CommandBufferDescriptor){.group = 0, .priority = 0});
}

void SceneGeomPass::render() {
  if (!bufferOpt_.has_value()) {
    return;
  }

  auto &buf = bufferOpt_->get();
  buf.enqueue(std::make_unique<BeginPassCommand>(*this));
  buf.enqueue(std::make_unique<DrawCommand>(gapi::TopologyType::Enum::TRIANGLE_STRIP));
  buf.enqueue(std::make_unique<EndPassCommand>());

  GraphicsPass::render();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
