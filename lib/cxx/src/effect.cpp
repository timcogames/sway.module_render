#include <sway/render/effect.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

auto Effect::create(const gapi::ShaderCreateInfoSet &infoSet) -> Effect::Ptr_t {
  auto *instance = new Effect(global::getGapiPluginFunctionSet(), infoSet);
  return instance;
}

Effect::Effect(global::GapiPluginFunctionSet *plug, const gapi::ShaderCreateInfoSet &infoSet)
    : gapiPlugin_(plug)
    , program_(nullptr) {
  program_ = gapiPlugin_->createShaderProgram();
  program_->attach(gapiPlugin_->createShader(infoSet.vs));
  program_->attach(gapiPlugin_->createShader(infoSet.fs));

  program_->link();
  if (!program_->isLinked()) {
    // Empty
  }

  program_->validate();
  if (!program_->isValidated()) {
    // Empty
  }
}

Effect::~Effect() { SAFE_DELETE_OBJECT(program_); }

void Effect::bind() { program_->use(); }

void Effect::unbind() { program_->unuse(); }

NAMESPACE_END(render)
NAMESPACE_END(sway)
