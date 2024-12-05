#ifndef SWAY_RENDER_TEST_SHADERPROGRAMSTUBCREATOR_H
#define SWAY_RENDER_TEST_SHADERPROGRAMSTUBCREATOR_H

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <google/stubs/shaderprogramstub.hpp>
#include <google/stubs/shaderstub.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

NS_BEGIN_SWAY()
NS_BEGIN(render)

struct ShaderProgramStubCreator {
  static auto create1(render::global::GapiPluginFunctionSet *plug, render::ShaderStub *shader)
      -> render::ShaderProgramStub * {
    auto *stub = new render::ShaderProgramStub();
    EXPECT_CALL(*plug, createShaderProgram()).WillRepeatedly(testing::Return(stub));
    EXPECT_CALL(*stub, attach(shader)).Times(2);
    EXPECT_CALL(*stub, link());
    EXPECT_CALL(*stub, isLinked()).WillOnce(testing::Return(true));
    EXPECT_CALL(*stub, validate());
    EXPECT_CALL(*stub, isValidated()).WillOnce(testing::Return(true));
    EXPECT_CALL(*stub, use());
    EXPECT_CALL(*stub, unuse());

    return stub;
  }

  static auto create2(render::global::GapiPluginFunctionSet *plug, render::ShaderStub *shader)
      -> render::ShaderProgramStub * {
    auto *stub = new render::ShaderProgramStub();
    EXPECT_CALL(*plug, createShaderProgram()).WillRepeatedly(testing::Return(stub));
    EXPECT_CALL(*stub, attach(shader)).Times(2);
    EXPECT_CALL(*stub, link());
    EXPECT_CALL(*stub, isLinked()).WillOnce(testing::Return(true));
    EXPECT_CALL(*stub, validate());
    EXPECT_CALL(*stub, isValidated()).WillOnce(testing::Return(true));
    ON_CALL(*stub, use()).WillByDefault([]() {});
    ON_CALL(*stub, unuse()).WillByDefault([]() {});

    return stub;
  }
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TEST_SHADERPROGRAMSTUBCREATOR_H
