#include <sway/render/effect.hpp>
#include <sway/render/global.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>

#include <algorithm>  // std::reverse

NS_BEGIN_SWAY()
NS_BEGIN(render)

RenderSubqueue::RenderSubqueue(RenderSubqueueGroup group)
    : group_(group) {
  matrixStack_ = std::make_shared<math::MatrixStack>();
  initialize();
}

void RenderSubqueue::initialize() { drawCall_ = global::getGapiPluginFunctionSet()->createDrawCall(); }

void RenderSubqueue::post(pipeline::ForwardRenderCommand cmd) { commands_.emplace_back(cmd); }

void RenderSubqueue::renderItem_(pipeline::ForwardRenderCommand cmd, gapi::StateContextPtr_t state) {
  state->setBlendEnable(cmd.blendDesc.enabled);
  if (cmd.blendDesc.enabled) {
    state->setBlendFn(cmd.blendDesc.src, cmd.blendDesc.dst);
    state->setColorMask(cmd.blendDesc.mask, cmd.blendDesc.mask, cmd.blendDesc.mask, cmd.blendDesc.mask);
    state->setDepthMask(cmd.blendDesc.mask);
  }

  state->setDepthEnable(cmd.depthDesc.enabled);
  if (cmd.depthDesc.enabled) {
    state->setDepthFn(cmd.depthDesc.func);
  }

  state->setStencilEnable(cmd.stencilDesc.enabled);
  if (cmd.stencilDesc.enabled) {
    state->setStencilFn(cmd.stencilDesc.front.func, cmd.stencilDesc.front.reference, cmd.stencilDesc.front.rmask);
    state->setStencilOp(cmd.stencilDesc.front.fail, cmd.stencilDesc.front.depthFail, cmd.stencilDesc.front.depthPass);
  }

  matrixStack_->push<math::MatrixType::Enum::PROJ>(cmd.proj);
  matrixStack_->push<math::MatrixType::Enum::VIEW>(cmd.view);
  matrixStack_->push<math::MatrixType::Enum::TFRM>(cmd.tfrm);

  cmd.mtrl->bind(matrixStack_);

  if (cmd.geom != nullptr) {
    cmd.geom->bind();

    gapi::BufferSet bufset;
    if (cmd.geom->getBuffer(Constants::IDX_VBO).has_value()) {
      bufset.vbo = cmd.geom->getBuffer(Constants::IDX_VBO).value();
    }

    if (cmd.geom->getBuffer(Constants::IDX_EBO).has_value()) {
      bufset.ebo = cmd.geom->getBuffer(Constants::IDX_EBO).value();
    } else {
      bufset.ebo = nullptr;
    }

    drawCall_->execute(cmd.topology, bufset, core::ValueDataType::Enum::UINT);

    cmd.geom->unbind();
  }

  cmd.mtrl->unbind();

  matrixStack_->pop<math::MatrixType::Enum::TFRM>();
  matrixStack_->pop<math::MatrixType::Enum::PROJ>();
  matrixStack_->pop<math::MatrixType::Enum::VIEW>();

  state->setStencilEnable(false);
  state->setDepthEnable(false);
  state->setBlendEnable(false);
}

void RenderSubqueue::render(u32_t stage, gapi::StateContextPtr_t state) {
  // std::reverse(commands_.begin(), commands_.end());
  for (const auto &cmd : commands_) {
    if (cmd.stage != stage) {
      break;
    }

    renderItem_(cmd, state);
  }

  commands_.clear();
}

NS_END()  // namespace render
NS_END()  // namespace sway
