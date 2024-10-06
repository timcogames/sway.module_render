
#ifndef PLUGTESTFIXTURE_H
#define PLUGTESTFIXTURE_H

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <gtest/gtest.h>

#include <gmock/gmock.h>

using namespace sway;

extern render::global::GapiPluginFunctionSet *globalGapiPlug;

class PlugTestFixture : public testing::Test {
public:
  MTHD_OVERRIDE(void SetUp());

  MTHD_OVERRIDE(void TearDown());

protected:
  render::global::MockPluginFunctionSet mockedGapiPlug;
};

inline auto createShaderStub(render::global::GapiPluginFunctionSet *plug) -> render::global::ShaderStub * {
  auto *shaderStub = new render::global::ShaderStub(gapi::ShaderType::Enum::NONE);
  EXPECT_CALL(*plug, createShader(testing::_)).WillRepeatedly(testing::Return(shaderStub));
  return shaderStub;
}

inline auto createShaderProgStub(render::global::GapiPluginFunctionSet *plug,
    render::global::ShaderStub *shader) -> render::global::ShaderProgramStub * {
  auto *shaderProgStub = new render::global::ShaderProgramStub();
  EXPECT_CALL(*plug, createShaderProgram()).WillRepeatedly(testing::Return(shaderProgStub));
  EXPECT_CALL(*shaderProgStub, attach(shader)).Times(2);
  EXPECT_CALL(*shaderProgStub, link());
  EXPECT_CALL(*shaderProgStub, isLinked()).WillOnce(testing::Return(true));
  EXPECT_CALL(*shaderProgStub, validate());
  EXPECT_CALL(*shaderProgStub, isValidated()).WillOnce(testing::Return(true));
  EXPECT_CALL(*shaderProgStub, use());
  EXPECT_CALL(*shaderProgStub, unuse());

  return shaderProgStub;
}

#endif  // PLUGTESTFIXTURE_H
