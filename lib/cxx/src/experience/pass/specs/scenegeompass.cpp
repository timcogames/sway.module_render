#include <sway/render/experience/command/specs/beginpasscommand.hpp>
#include <sway/render/experience/command/specs/clearcommand.hpp>
#include <sway/render/experience/command/specs/drawcommand.hpp>
#include <sway/render/experience/command/specs/endpasscommand.hpp>
#include <sway/render/experience/pass/specs/scenegeompass.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

SceneGeomPass::SceneGeomPass(const PassDescriptor &desc)
    : GraphicsPass(desc) {}

void SceneGeomPass::setup() {
  bufferOpt_ = CommandBuffer::create(this->getQueue(), (struct CommandBufferDescriptor){.priority = 0});
}

void SceneGeomPass::execute(OperationContext *ctx) {
  if (!bufferOpt_.has_value()) {
    return;
  }

  auto &buf = bufferOpt_->get();
  buf.enqueue(std::make_unique<BeginPassCommand>(*this));
  buf.enqueue(std::make_unique<ClearCommand>(math::col4f_t(0.0F, 0.0F, 0.0F, 255.0F), gapi::ClearFlag::COLOR));
  buf.enqueue(std::make_unique<DrawCommand>(gapi::TopologyType::Enum::TRIANGLE_STRIP));
  buf.enqueue(std::make_unique<EndPassCommand>());

  GraphicsPass::execute(ctx);
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
