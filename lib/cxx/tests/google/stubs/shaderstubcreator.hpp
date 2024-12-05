#ifndef SWAY_RENDER_TEST_SHADERSTUBCREATOR_H
#define SWAY_RENDER_TEST_SHADERSTUBCREATOR_H

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <google/stubs/shaderstub.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

NS_BEGIN_SWAY()
NS_BEGIN(render)

struct ShaderStubCreator {
  static auto create(render::global::GapiPluginFunctionSet *plug) -> render::ShaderStub * {
    auto *stub = new render::ShaderStub(gapi::ShaderType::Enum::NONE);
    EXPECT_CALL(*plug, createShader(testing::_)).WillRepeatedly(testing::Return(stub));

    return stub;
  }
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TEST_SHADERSTUBCREATOR_H
