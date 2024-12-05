#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <google/plugfixture.hpp>
#include <google/stubs/shaderprogramstubcreator.hpp>
#include <google/stubs/shaderstubcreator.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

NS_SHORT_SWAY()

class EffectTestFixture : public PlugTestFixture {};

TEST_F(EffectTestFixture, create_buffer) {
  auto *shaderStub = render::ShaderStubCreator::create(globalGapiPlug);
  auto *shaderProgStub = render::ShaderProgramStubCreator::create1(globalGapiPlug, shaderStub);

  gapi::ShaderCreateInfoSet infoSet;
  infoSet.vs.type = gapi::ShaderType::Enum::VERT;
  infoSet.vs.code = "";
  infoSet.fs.type = gapi::ShaderType::Enum::FRAG;
  infoSet.fs.code = "";
  auto *effect = new render::Effect(globalGapiPlug, infoSet);

  effect->bind();
  effect->unbind();

  SAFE_DELETE_OBJECT(shaderStub);
  SAFE_DELETE_OBJECT(shaderProgStub);
}

TEST_F(EffectTestFixture, reload) {
  auto *shaderStub = render::ShaderStubCreator::create(globalGapiPlug);
  auto *shaderProgStub = render::ShaderProgramStubCreator::create2(globalGapiPlug, shaderStub);

  gapi::ShaderCreateInfoSet infoSet;
  infoSet.vs.type = gapi::ShaderType::Enum::VERT;
  infoSet.vs.code = "";
  infoSet.fs.type = gapi::ShaderType::Enum::FRAG;
  infoSet.fs.code = "";
  auto *effect = new render::Effect(globalGapiPlug, infoSet);

  effect->reload("./wwwroot/dist/assets/materials/empty.json");

  SAFE_DELETE_OBJECT(shaderStub);
  SAFE_DELETE_OBJECT(shaderProgStub);
}
