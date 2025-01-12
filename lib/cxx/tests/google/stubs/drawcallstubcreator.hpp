#ifndef SWAY_RENDER_TEST_DRAWCALLSTUBCREATOR_H
#define SWAY_RENDER_TEST_DRAWCALLSTUBCREATOR_H

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <google/stubs/drawcallstub.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace sway::render {

struct DrawCallStubCreator {
  static auto create(render::global::GapiPluginFunctionSet *plug) -> render::DrawCallStub * {
    auto *stub = new render::DrawCallStub();
    EXPECT_CALL(*plug, createDrawCall()).WillRepeatedly(testing::Return(stub));
    EXPECT_CALL(*stub, execute(testing::_, testing::_, testing::_)).WillOnce(testing::Return());

    return stub;
  }
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_DRAWCALLSTUBCREATOR_H
