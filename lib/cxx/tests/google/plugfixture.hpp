#ifndef PLUGTESTFIXTURE_H
#define PLUGTESTFIXTURE_H

#include <sway/core.hpp>
#include <sway/render.hpp>
#include <sway/render/global.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

NS_SHORT_SWAY()

extern render::global::GapiPluginFunctionSet *globalGapiPlug;

class PlugTestFixture : public testing::Test {
public:
#pragma region "Override testing::Test methods"

  MTHD_OVERRIDE(void SetUp());

  MTHD_OVERRIDE(void TearDown());

#pragma endregion

protected:
  render::global::MockPluginFunctionSet mockedGapiPlug;
};

#endif  // PLUGTESTFIXTURE_H
