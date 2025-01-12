#ifndef SWAY_RENDER_TEST_VIEWPORTSTUBCREATOR_H
#define SWAY_RENDER_TEST_VIEWPORTSTUBCREATOR_H

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <google/stubs/viewportstub.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace sway::render {

struct ViewportStubCreator {
  static auto create(render::global::GapiPluginFunctionSet *plug) -> render::ViewportStub * {
    auto *stub = new render::ViewportStub();
    EXPECT_CALL(*plug, createViewport()).WillRepeatedly(testing::Return(stub));
    EXPECT_CALL(*stub, setClearColor(testing::_));
    EXPECT_CALL(*stub, clear(testing::_));

    return stub;
  }
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_VIEWPORTSTUBCREATOR_H
