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

void RenderSubqueue::initialize() { drawCall_ = global::getGapiFunctionSet()->createDrawCall(); }

void RenderSubqueue::post(pipeline::ForwardRenderCommand cmd) { commands_.emplace_back(cmd); }

void RenderSubqueue::render(u32_t stage, std::shared_ptr<gapi::StateContext> state) {
  for (const auto &cmd : commands_) {
    if (cmd.stage != stage) {
      break;
    }

    state->setBlendEnable(cmd.blendDesc.enabled);
    state->setBlendFn(cmd.blendDesc.src, cmd.blendDesc.dst);
    state->setDepthEnable(cmd.depthDesc.enabled);
    state->setDepthFn(cmd.depthDesc.func);
    state->setStencilEnable(cmd.stencilDesc.enabled);
    state->setStencilFn(cmd.stencilDesc.front.func, cmd.stencilDesc.front.reference, cmd.stencilDesc.front.rmask);
    state->setStencilOp(cmd.stencilDesc.front.fail, cmd.stencilDesc.front.depthFail, cmd.stencilDesc.front.depthPass);
    state->setColorMask(cmd.blendDesc.mask, cmd.blendDesc.mask, cmd.blendDesc.mask, cmd.blendDesc.mask);
    state->setDepthMask(cmd.blendDesc.mask);

    matrixStack_->push<math::MatrixType::PROJ>(cmd.proj);
    matrixStack_->push<math::MatrixType::VIEW>(cmd.view);
    matrixStack_->push<math::MatrixType::TFRM>(cmd.tfrm);

    cmd.material->bind(matrixStack_);
    cmd.geometry->bind();

    drawCall_->execute(cmd.geometry->getTopology(), cmd.geometry->getBufferSet(), core::ValueDataType::UINT);

    cmd.geometry->unbind();
    cmd.material->unbind();

    matrixStack_->pop<math::MatrixType::TFRM>();
    matrixStack_->pop<math::MatrixType::PROJ>();
    matrixStack_->pop<math::MatrixType::VIEW>();

    state->setStencilEnable(false);
    state->setDepthEnable(false);
  }

  commands_.clear();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)