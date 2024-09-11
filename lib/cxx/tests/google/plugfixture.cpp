#include <google/plugfixture.hpp>

sway::render::global::GapiPluginFunctionSet *globalGapiPlug = nullptr;

void PlugTestFixture::SetUp() { globalGapiPlug = &mockedGapiPlug; }

void PlugTestFixture::TearDown() { globalGapiPlug = nullptr; }
