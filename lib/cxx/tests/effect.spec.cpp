#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace sway;

render::global::GapiPluginFunctionSet *globalGapiPlugCopy;

class EffectTestFixture : public testing::Test {
protected:
  render::global::MockPluginFunctionSet mockedGapiPlug;

  void SetUp() { globalGapiPlugCopy = &mockedGapiPlug; }

  void TearDown() { globalGapiPlugCopy = nullptr; }
};

TEST_F(EffectTestFixture, createBuffer) {
  auto *shaderStub = new render::global::ShaderStub(gapi::ShaderType::NONE);
  EXPECT_CALL(*globalGapiPlugCopy, createShader(testing::_)).WillRepeatedly(testing::Return(shaderStub));

  auto *shaderProgramStub = new render::global::ShaderProgramStub();
  EXPECT_CALL(*globalGapiPlugCopy, createShaderProgram()).WillRepeatedly(testing::Return(shaderProgramStub));
  EXPECT_CALL(*shaderProgramStub, attach(shaderStub)).Times(2);
  EXPECT_CALL(*shaderProgramStub, link());
  EXPECT_CALL(*shaderProgramStub, isLinked()).WillOnce(testing::Return(true));
  EXPECT_CALL(*shaderProgramStub, validate());
  EXPECT_CALL(*shaderProgramStub, isValidated()).WillOnce(testing::Return(true));
  EXPECT_CALL(*shaderProgramStub, use());
  EXPECT_CALL(*shaderProgramStub, unuse());

  gapi::ShaderCreateInfoSet infoSet;
  infoSet.vs.type = gapi::ShaderType::VERT;
  infoSet.vs.code = "";
  infoSet.fs.type = gapi::ShaderType::FRAG;
  infoSet.fs.code = "";
  auto *effect = new render::Effect(globalGapiPlugCopy, infoSet);

  effect->bind();
  effect->unbind();

  SAFE_DELETE_OBJECT(shaderStub);
  SAFE_DELETE_OBJECT(shaderProgramStub);
}
