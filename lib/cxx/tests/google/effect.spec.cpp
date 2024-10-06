#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <gtest/gtest.h>

#include <gmock/gmock.h>
#include <google/plugfixture.hpp>

using namespace sway;

class EffectTestFixture : public PlugTestFixture {};

TEST_F(EffectTestFixture, create_buffer) {
  auto *shaderStub = createShaderStub(globalGapiPlug);
  auto *shaderProgStub = createShaderProgStub(globalGapiPlug, shaderStub);

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
