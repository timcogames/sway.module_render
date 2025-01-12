#ifndef SWAY_RENDER_GLOBAL_HPP
#define SWAY_RENDER_GLOBAL_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/idgenerator.hpp>

#ifdef RENDER_USE_GMOCK
#  include <gmock/gmock.h>
#endif

namespace sway::render {
NS_BEGIN(global)

#ifdef RENDER_USE_GMOCK

struct MockPluginFunctionSet : public gapi::PluginFunctionSetInterface {
#  pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  DTOR_VIRTUAL_DEFAULT(MockPluginFunctionSet);

  /** @} */
#  pragma endregion

  MOCK_METHOD(gapi::typedefs::CapabilityPtr_t, createCapability, (), (override));
  MOCK_METHOD(gapi::typedefs::ShaderPtr_t, createShader, (const gapi::ShaderCreateInfo &), (override));
  MOCK_METHOD(gapi::typedefs::ShaderProgramPtr_t, createShaderProgram, (), (override));
  MOCK_METHOD(gapi::typedefs::IdGeneratorPtr_t, createBufferIdGenerator, (), (override));
  MOCK_METHOD(gapi::typedefs::BufferPtr_t, createBuffer,
      (gapi::typedefs::IdGeneratorPtr_t, const gapi::BufferCreateInfo &), (override));
  MOCK_METHOD(gapi::typedefs::IdGeneratorPtr_t, createFrameBufferIdGenerator, (), (override));
  MOCK_METHOD(gapi::typedefs::FrameBufferPtr_t, createFrameBuffer, (gapi::typedefs::IdGeneratorPtr_t), (override));
  MOCK_METHOD(gapi::typedefs::RenderBufferPtr_t, createRenderBuffer, (), (override));
  MOCK_METHOD(gapi::typedefs::VertexArrayPtr_t, createVertexArray, (), (override));
  MOCK_METHOD(gapi::typedefs::VertexAttribLayoutPtr_t, createVertexAttribLayout, (gapi::typedefs::ShaderProgramPtr_t),
      (override));
  MOCK_METHOD(gapi::typedefs::IdGeneratorPtr_t, createTextureIdGenerator, (), (override));
  MOCK_METHOD(gapi::typedefs::TexturePtr_t, createTexture,
      (gapi::typedefs::IdGeneratorPtr_t, const gapi::TextureCreateInfo &), (override));
  MOCK_METHOD(gapi::typedefs::TextureSamplerPtr_t, createTextureSampler, (gapi::typedefs::TexturePtr_t), (override));
  MOCK_METHOD(gapi::typedefs::DrawCallPtr_t, createDrawCall, (), (override));
  MOCK_METHOD(gapi::typedefs::ViewportPtr_t, createViewport, (), (override));
  MOCK_METHOD(gapi::typedefs::StateContextPtr_t, createStateContext, (), (override));
  MOCK_METHOD(gapi::typedefs::ShaderPreprocessorPtr_t, createShaderPreprocessor, (u32_t, lpcstr_t), (override));
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
}  // namespace sway::render

#endif  // SWAY_RENDER_GLOBAL_HPP
