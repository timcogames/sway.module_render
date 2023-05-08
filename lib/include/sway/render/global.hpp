#ifndef SWAY_RENDER_GLOBAL_HPP
#define SWAY_RENDER_GLOBAL_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#ifdef _MOCK
#  include <gmock/gmock.h>
#else
#endif

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(global)

#ifdef _MOCK

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
  MOCK_METHOD(gapi::VertexAttribLayoutPtr_t, createVertexAttribLayout, (gapi::ShaderProgramRef_t));
  MOCK_METHOD(gapi::TextureRef_t, createTexture, ());
  MOCK_METHOD(gapi::TextureSamplerRef_t, createTextureSampler, ());
  MOCK_METHOD(gapi::DrawCallRef_t, createDrawCall, ());
  MOCK_METHOD(gapi::ViewportRef_t, createViewport, ());
};

extern core::Plugin *pluginInstance_;
extern MockPluginFunctionSet *pluginFunctionSet_;

auto getGapiFunctionSet() -> MockPluginFunctionSet *;

#else

extern core::Plugin *pluginInstance_;
extern gapi::ConcreatePluginFunctionSet *pluginFunctionSet_;

auto getGapiFunctionSet() -> gapi::ConcreatePluginFunctionSet *;

#endif

NAMESPACE_END(global)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GLOBAL_HPP
