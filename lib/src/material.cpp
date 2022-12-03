#include <sway/graphics/material.hpp>
#include <sway/graphics/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Material::Material(const gapi::ShaderCreateInfoSet &infoSet) {
  auto *pluginFuncSet = global::getGapiFunctionSet();

  shaderProgram_ = pluginFuncSet->createShaderProgram();
  shaderProgram_->attach(pluginFuncSet->createShader(infoSet.vs));
  shaderProgram_->attach(pluginFuncSet->createShader(infoSet.fs));

  shaderProgram_->link();
  if (shaderProgram_->isLinked()) {
    // Empty
  }

  shaderProgram_->validate();
  if (shaderProgram_->isValidated()) {
    // Empty
  }
}

void Material::loadFromXml() {
  // Empty
}

void Material::bind() { shaderProgram_->use(); }

void Material::unbind() { shaderProgram_->unuse(); }

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
