#ifndef SWAY_RENDER_TEST_SHADERPREPROCESSORSTUBCREATOR_H
#define SWAY_RENDER_TEST_SHADERPREPROCESSORSTUBCREATOR_H

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <google/stubs/shaderpreprocessorstub.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace sway::render {

struct ShaderPreprocessorStubCreator {
  static auto create(render::global::GapiPluginFunctionSet *plug) -> render::ShaderPreprocessorStub * {
    auto *stub = new render::ShaderPreprocessorStub();
    // EXPECT_CALL(*plug, createShaderPreprocessor(testing::_, testing::_)).WillRepeatedly(testing::Return(stub));
    // EXPECT_CALL(*stub, addDefine(testing::_, testing::_)).Times(1);
    // EXPECT_CALL(*stub, hasDefined(testing::_)).WillOnce(testing::Return(true));

    return stub;
  }
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_SHADERPREPROCESSORSTUBCREATOR_H
