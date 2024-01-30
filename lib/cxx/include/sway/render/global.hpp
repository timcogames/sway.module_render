#ifndef SWAY_RENDER_GLOBAL_HPP
#define SWAY_RENDER_GLOBAL_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#ifdef RENDER_USE_GMOCK
#  include <gmock/gmock.h>
#endif

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(global)

#ifdef RENDER_USE_GMOCK

class CapabilityMock {
public:
  MOCK_METHOD(core::Version, getVersion, (), (const));
};

struct MockPluginFunctionSet : public core::PluginFunctionSet {
  MOCK_METHOD(gapi::CapabilityRef_t, createCapability, ());
  MOCK_METHOD(gapi::ShaderRef_t, createShader, (const gapi::ShaderCreateInfo &));
  MOCK_METHOD(gapi::ShaderProgramRef_t, createShaderProgram, ());
  MOCK_METHOD(gapi::IdGeneratorRef_t, createIdGenerator, ());
  MOCK_METHOD(gapi::BufferRef_t, createBuffer, (gapi::IdGeneratorRef_t, const gapi::BufferCreateInfo &));
  MOCK_METHOD(gapi::VertexArrayPtr_t, createVertexArray, ());
  MOCK_METHOD(gapi::VertexAttribLayoutPtr_t, createVertexAttribLayout, (gapi::ShaderProgramRef_t));
  MOCK_METHOD(gapi::TextureRef_t, createTexture, (const gapi::TextureCreateInfo &));
  MOCK_METHOD(gapi::TextureSamplerRef_t, createTextureSampler, ());
  MOCK_METHOD(gapi::DrawCallRef_t, createDrawCall, ());
  MOCK_METHOD(gapi::ViewportRef_t, createViewport, ());
  MOCK_METHOD(gapi::StateContextRef_t, createStateContext, ());
};

using GapiPluginFunctionSet = MockPluginFunctionSet;

#else

using GapiPluginFunctionSet = gapi::ConcreatePluginFunctionSet;

#endif

extern core::Plugin *pluginInstance_;
extern GapiPluginFunctionSet *pluginFunctionSet_;

auto getGapiPluginFunctionSet() -> GapiPluginFunctionSet *;

NAMESPACE_END(global)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GLOBAL_HPP
