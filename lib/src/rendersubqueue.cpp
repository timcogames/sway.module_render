#include <sway/render/effect.hpp>
#include <sway/render/geometry.hpp>
#include <sway/render/global.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

RenderSubqueue::RenderSubqueue(RenderSubqueueGroup group)
    : group_(group) {
  matrixStack_ = std::make_shared<math::MatrixStack>();
}

void RenderSubqueue::initialize() {
  drawCall_ = global::getGapiFunctionSet()->createDrawCall();
  state_ = global::getGapiFunctionSet()->createState();
}

void RenderSubqueue::post(pipeline::ForwardRenderCommand cmd) { commands_.emplace_back(cmd); }

void RenderSubqueue::render(u32_t stage) {
  for (const auto &cmd : commands_) {
    if (cmd.stage != stage) {
      break;
    }

    matrixStack_->push<math::MatrixType::PROJ>(cmd.proj);
    matrixStack_->push<math::MatrixType::VIEW>(cmd.view);
    matrixStack_->push<math::MatrixType::MODEL>(cmd.tfrm);

    cmd.material->bind(matrixStack_);
    cmd.geometry->bind();

    drawCall_->execute(cmd.geometry->getTopology(), cmd.geometry->getBufferSet(), core::ValueDataType::UInt);

    cmd.geometry->unbind();
    cmd.material->unbind();

    matrixStack_->pop<math::MatrixType::MODEL>();
    matrixStack_->pop<math::MatrixType::PROJ>();
    matrixStack_->pop<math::MatrixType::VIEW>();
  }

  commands_.clear();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
