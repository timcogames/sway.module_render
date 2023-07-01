#include <sway/math.hpp>
#include <sway/render/effect.hpp>
#include <sway/render/geometry.hpp>
#include <sway/render/global.hpp>
#include <sway/render/rendersubqueue.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

RenderSubqueue::RenderSubqueue(RenderSubqueueGroup group)
    : group_(group) {}

void RenderSubqueue::initialize() {
  drawCall_ = global::getGapiFunctionSet()->createDrawCall();
  state_ = global::getGapiFunctionSet()->createState();
}

void RenderSubqueue::post(pipeline::ForwardRenderCommand command) { commands_.emplace_back(command); }

void RenderSubqueue::render() {
  auto matrixStack = std::make_shared<math::MatrixStack>();
  gapi::BufferSet bufset = {nullptr, nullptr};

  for (const auto &cmd : commands_) {
    matrixStack->push<math::MatrixType::PROJ>(cmd.proj);
    matrixStack->push<math::MatrixType::VIEW>(cmd.view);
    matrixStack->push<math::MatrixType::MODEL>(cmd.transform);

    bufset.vbo = cmd.geometry->getVertexBuffer();
    bufset.ibo = cmd.geometry->getIndexBuffer();

    if (cmd.images.size() > 0) {
      cmd.effect->getShaderProgram()->setUniform1i("diffuse_sampler", cmd.images[0]->getTexture()->getUid().value());
    }

    // auto matViewProj = matrixStack->top<math::MatrixType::PROJ>() * matrixStack->top<math::MatrixType::VIEW>();
    auto matViewProj = matrixStack->top<math::MatrixType::VIEW>() * matrixStack->top<math::MatrixType::PROJ>();
    // std::cout << matProjView << std::endl;

    cmd.effect->getShaderProgram()->setUniformMat4f("mat_proj", matrixStack->top<math::MatrixType::PROJ>());
    cmd.effect->getShaderProgram()->setUniformMat4f("mat_view", matrixStack->top<math::MatrixType::VIEW>());
    cmd.effect->getShaderProgram()->setUniformMat4f("mat_view_proj", matViewProj);
    cmd.effect->getShaderProgram()->setUniformMat4f("mat_model", matrixStack->top<math::MatrixType::MODEL>());
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

    matrixStack->pop<math::MatrixType::MODEL>();
    matrixStack->pop<math::MatrixType::VIEW>();
    matrixStack->pop<math::MatrixType::PROJ>();
  }

  commands_.clear();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
