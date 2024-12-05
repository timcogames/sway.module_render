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

struct MockPluginFunctionSetInterface : public core::PluginFunctionSet {
#  pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(MockPluginFunctionSetInterface);

#  pragma endregion

  // clang-format off
  PURE_VIRTUAL(auto createCapability() -> gapi::CapabilityPtr_t);
  PURE_VIRTUAL(auto createShader(const gapi::ShaderCreateInfo &) -> gapi::ShaderPtr_t);
  PURE_VIRTUAL(auto createShaderProgram() -> gapi::ShaderProgramPtr_t);
  PURE_VIRTUAL(auto createBufferIdGenerator() -> gapi::IdGeneratorPtr_t);
  PURE_VIRTUAL(auto createBuffer(gapi::IdGeneratorPtr_t, const gapi::BufferCreateInfo &) -> gapi::BufferPtr_t);
  PURE_VIRTUAL(auto createFrameBufferIdGenerator() -> gapi::IdGeneratorPtr_t);
  PURE_VIRTUAL(auto createFrameBuffer(gapi::IdGeneratorPtr_t) -> gapi::FrameBufferPtr_t);
  PURE_VIRTUAL(auto createRenderBuffer() -> gapi::RenderBufferPtr_t);
  PURE_VIRTUAL(auto createVertexArray() -> gapi::VertexArrayPtr_t);
  PURE_VIRTUAL(auto createVertexAttribLayout(gapi::ShaderProgramPtr_t) -> gapi::VertexAttribLayoutPtr_t);
  PURE_VIRTUAL(auto createTextureIdGenerator() -> gapi::IdGeneratorPtr_t);
  PURE_VIRTUAL(auto createTexture(gapi::IdGeneratorPtr_t, const gapi::TextureCreateInfo &) -> gapi::TexturePtr_t);
  PURE_VIRTUAL(auto createTextureSampler(gapi::TexturePtr_t) -> gapi::TextureSamplerPtr_t);
  PURE_VIRTUAL(auto createDrawCall() -> gapi::DrawCallPtr_t);
  PURE_VIRTUAL(auto createViewport() -> gapi::ViewportPtr_t);
  PURE_VIRTUAL(auto createStateContext() -> gapi::StateContextPtr_t);
  PURE_VIRTUAL(auto createShaderPreprocessor(u32_t, lpcstr_t) -> gapi::ShaderPreprocessor::Ptr_t);
  PURE_VIRTUAL(auto createRasterizerState() -> gapi::StateEnableable<gapi::RasterizerDescriptor> *);
  // clang-format on
};

struct MockPluginFunctionSet : public MockPluginFunctionSetInterface {
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
