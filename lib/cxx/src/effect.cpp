#include <sway/render/effect.hpp>
#include <sway/render/global.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Effect::Effect(const gapi::ShaderCreateInfoSet &infoSet) {
  auto *pluginFuncSet = global::getGapiFunctionSet();

  program_ = pluginFuncSet->createShaderProgram();
  program_->attach(pluginFuncSet->createShader(infoSet.vs));
  program_->attach(pluginFuncSet->createShader(infoSet.fs));

  program_->link();
  if (!program_->isLinked()) {
    // Empty
  }

  program_->validate();
  if (!program_->isValidated()) {
    // Empty
  }
}

void Effect::bind() { program_->use(); }

void Effect::unbind() { program_->unuse(); }

NAMESPACE_END(render)
NAMESPACE_END(sway)
