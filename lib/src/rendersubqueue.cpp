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

void RenderSubqueue::render() {
  gapi::BufferSet bufset = {nullptr, nullptr};

  for (const auto &cmd : commands_) {
    matrixStack_->push<math::MatrixType::PROJ>(cmd.proj);
    matrixStack_->push<math::MatrixType::VIEW>(cmd.view);
    matrixStack_->push<math::MatrixType::MODEL>(cmd.transform);

    bufset.vbo = cmd.geometry->getVertexBuffer();
    bufset.ibo = cmd.geometry->getIndexBuffer();

    if (!cmd.images.empty()) {
      cmd.effect->getShaderProgram()->setUniform1i("diffuse_sampler", cmd.images[0]->getTexture()->getUid().value());
    }

    auto viewMat = matrixStack_->top<math::MatrixType::VIEW>();
    auto projMat = matrixStack_->top<math::MatrixType::PROJ>();
    auto matViewProj = viewMat * projMat;

    cmd.effect->getShaderProgram()->setUniformMat4f("mat_view", viewMat);
    cmd.effect->getShaderProgram()->setUniformMat4f("mat_proj", projMat);
    cmd.effect->getShaderProgram()->setUniformMat4f("mat_view_proj", matViewProj);
    cmd.effect->getShaderProgram()->setUniformMat4f("mat_model", matrixStack_->top<math::MatrixType::MODEL>());
    cmd.effect->bind();

    cmd.geometry->bind();

    for (auto image : cmd.images) {
      state_->apply();

      image->getTexture()->setActive(cmd.images[0]->getTexture()->getUid().value());
      image->bind();
    }

    if (drawCall_) {
      drawCall_->execute(cmd.geometry->getTopology(), bufset, core::ValueDataType::UInt);
    }

    for (auto image : cmd.images) {
      image->unbind();
    }

    cmd.geometry->unbind();

    cmd.effect->unbind();

    matrixStack_->pop<math::MatrixType::MODEL>();
    matrixStack_->pop<math::MatrixType::VIEW>();
    matrixStack_->pop<math::MatrixType::PROJ>();
  }

  commands_.clear();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
