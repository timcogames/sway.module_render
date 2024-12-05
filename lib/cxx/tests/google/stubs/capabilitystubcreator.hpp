#ifndef SWAY_RENDER_TEST_CAPABILITYSTUBCREATOR_H
#define SWAY_RENDER_TEST_CAPABILITYSTUBCREATOR_H

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <google/stubs/capabilitystub.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

NS_BEGIN_SWAY()
NS_BEGIN(render)

struct CapabilityStubCreator {
  static auto create(render::global::GapiPluginFunctionSet *plug) -> render::CapabilityStub * {
    auto *stub = new render::CapabilityStub();
    EXPECT_CALL(*plug, createCapability()).WillRepeatedly(testing::Return(stub));
    // EXPECT_CALL(*stub, getVersion()).WillOnce(testing::Return(core::Version(1, 0, 0)));

    return stub;
  }
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TEST_CAPABILITYSTUBCREATOR_H
