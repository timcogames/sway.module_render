#ifndef SWAY_RENDER_GLOBAL_HPP
#define SWAY_RENDER_GLOBAL_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/idgenerator.hpp>

#ifdef RENDER_USE_GMOCK
#  include <gmock/gmock.h>
#endif

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(global)

#ifdef RENDER_USE_GMOCK

struct MockPluginFunctionSet : public gapi::PluginFunctionSetInterface {
#  pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(MockPluginFunctionSet);

#  pragma endregion

  MOCK_METHOD(gapi::CapabilityPtr_t, createCapability, (), (override));
  MOCK_METHOD(gapi::ShaderPtr_t, createShader, (const gapi::ShaderCreateInfo &), (override));
  MOCK_METHOD(gapi::ShaderProgramPtr_t, createShaderProgram, (), (override));
  MOCK_METHOD(gapi::IdGeneratorPtr_t, createBufferIdGenerator, (), (override));
  MOCK_METHOD(gapi::BufferPtr_t, createBuffer, (gapi::IdGeneratorPtr_t, const gapi::BufferCreateInfo &), (override));
  MOCK_METHOD(gapi::IdGeneratorPtr_t, createFrameBufferIdGenerator, (), (override));
  MOCK_METHOD(gapi::FrameBufferPtr_t, createFrameBuffer, (gapi::IdGeneratorPtr_t), (override));
  MOCK_METHOD(gapi::RenderBufferPtr_t, createRenderBuffer, (), (override));
  MOCK_METHOD(gapi::VertexArrayPtr_t, createVertexArray, (), (override));
  MOCK_METHOD(gapi::VertexAttribLayoutPtr_t, createVertexAttribLayout, (gapi::ShaderProgramPtr_t), (override));
  MOCK_METHOD(gapi::IdGeneratorPtr_t, createTextureIdGenerator, (), (override));
  MOCK_METHOD(gapi::TexturePtr_t, createTexture, (gapi::IdGeneratorPtr_t, const gapi::TextureCreateInfo &), (override));
  MOCK_METHOD(gapi::TextureSamplerPtr_t, createTextureSampler, (gapi::TexturePtr_t), (override));
  MOCK_METHOD(gapi::DrawCallPtr_t, createDrawCall, (), (override));
  MOCK_METHOD(gapi::ViewportPtr_t, createViewport, (), (override));
  MOCK_METHOD(gapi::StateContextPtr_t, createStateContext, (), (override));
  MOCK_METHOD(gapi::ShaderPreprocessor::Ptr_t, createShaderPreprocessor, (u32_t, lpcstr_t), (override));
  MOCK_METHOD(gapi::StateEnableable<gapi::RasterizerDescriptor> *, createRasterizerState, (), (override));
};

using GapiPluginFunctionSet = MockPluginFunctionSet;

#else

using GapiPluginFunctionSet = gapi::ConcreatePluginFunctionSet;

#endif  // RENDER_USE_GMOCK

extern core::Plugin *pluginInstance_;
extern GapiPluginFunctionSet *pluginFunctionSet_;

auto getGapiPluginFunctionSet() -> GapiPluginFunctionSet *;

NS_END()  // namespace global
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_GLOBAL_HPP
