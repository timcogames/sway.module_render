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

class CapabilityMock {
public:
  MOCK_METHOD(core::Version, getVersion, (), (const));
};

class ViewportStub : public gapi::Viewport {
public:
#  pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(ViewportStub);

#  pragma endregion

  MOCK_METHOD(void, set, (i32_t, i32_t, i32_t, i32_t), (override));
  MOCK_METHOD(void, set, (i32_t, i32_t), (override));
  MOCK_METHOD(math::rect4i_t, get, (), (const override));
  MOCK_METHOD(f32_t, aspect, (), (const override));
  MOCK_METHOD(void, setClearColor, (const math::col4f_t &), (override));
  MOCK_METHOD(void, clear, (gapi::ClearFlag), (override));
};

class ShaderProgramStub : public gapi::ShaderProgram {
public:
#  pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(ShaderProgramStub);

#  pragma endregion

  MOCK_METHOD(void, attach, (gapi::ShaderPtr_t), (override));
  MOCK_METHOD(void, detach, ((std::pair<gapi::ShaderType::Enum, gapi::ShaderPtr_t>), bool), (override));
  MOCK_METHOD(gapi::ShaderPtr_t, getShader, (gapi::ShaderType::Enum), (override));
  MOCK_METHOD(void, link, (), (override));
  MOCK_METHOD(bool, isLinked, (), (const, override));
  MOCK_METHOD(void, validate, (), (override));
  MOCK_METHOD(bool, isValidated, (), (const, override));
  MOCK_METHOD(void, use, (), (override));
  MOCK_METHOD(void, unuse, (), (override));
  MOCK_METHOD(bool, isUsed, (), (const, override));
  MOCK_METHOD(void, setUniformVec4f, (const std::string &, const math::vec4f_t &), (override));
  MOCK_METHOD(void, setUniformCol4f, (const std::string &, const math::col4f_t &), (override));
  MOCK_METHOD(void, setUniformMat4f, (const std::string &, const math::mat4f_t &), (override));
  MOCK_METHOD(void, setUniform1i, (const std::string &, i32_t), (override));
  MOCK_METHOD(void, setUniform1f, (const std::string &, f32_t), (override));
};

class ShaderStub : public gapi::Shader {
public:
#  pragma region "Ctors/Dtor"

  ShaderStub(gapi::ShaderType::Enum type)
      : gapi::Shader(type) {}

  DTOR_VIRTUAL_DEFAULT(ShaderStub);

#  pragma endregion

  MOCK_METHOD(void, compile, (lpcstr_t), (override));
  MOCK_METHOD(bool, isCompiled, (), (const, override));
  MOCK_METHOD(i32_t, getAttribLocation, (std::optional<u32_t>, lpcstr_t), (override));
  MOCK_METHOD(gapi::ShaderType::Enum, getType, (), (const, override));
};

class IdGeneratorStub : public gapi::IdGenerator {
public:
#  pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(IdGeneratorStub);

#  pragma endregion

  MOCK_METHOD(u32_t, getNextUid, (), (override));
};

class VertexArrayStub : public gapi::VertexArray {
public:
#  pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(VertexArrayStub);

#  pragma endregion

  MOCK_METHOD(void, bind, (), (override));
  MOCK_METHOD(void, unbind, (), (override));
};

class BufferStub : public gapi::Buffer {
public:
#  pragma region "Ctors/Dtor"

  BufferStub()
      : gapi::Buffer(gapi::BufferDescriptor()) {}

  DTOR_VIRTUAL_DEFAULT(BufferStub);

#  pragma endregion

  MOCK_METHOD(bool, allocate, (const void *), (override));
  MOCK_METHOD(void, updateSubdata, (gapi::BufferSubdataDescriptor), (override));
  MOCK_METHOD(void, updateSubdata, (const void *), (override));
  MOCK_METHOD(void, flush, (i32_t, i32_t), (override));
  MOCK_METHOD(void *, map, (gapi::BufferMapAccess::Enum), (override));
  MOCK_METHOD(
      void *, mapRange, (i32_t, i32_t, core::detail::EnumClassBitset<gapi::BufferMapRangeAccess::Enum>), (override));
  MOCK_METHOD(void, unmap, (), (override));
  MOCK_METHOD(void, bindRange, (u32_t, ptrdiff_t, ptrdiff_t), (override));
  MOCK_METHOD(void, bind, (), (override));
  MOCK_METHOD(void, unbind, (), (override));
  MOCK_METHOD(gapi::BufferTarget::Enum, getTarget, (), (const, override));
  MOCK_METHOD(gapi::BufferUsage::Enum, getUsage, (), (const, override));
  MOCK_METHOD(i32_t, getCapacity, (), (const, override));
  MOCK_METHOD(i32_t, getByteStride, (), (const, override));
};

class VertexAttribLayoutStub : public gapi::VertexAttribLayout {
public:
#  pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(VertexAttribLayoutStub);

#  pragma endregion

  MOCK_METHOD(void, addAttribute, (gapi::VertexAttribDescriptor), (override));
  MOCK_METHOD(void, enable, (), (override));
  MOCK_METHOD(void, disable, (), (override));
};

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

#endif

extern core::Plugin *pluginInstance_;
extern GapiPluginFunctionSet *pluginFunctionSet_;

auto getGapiPluginFunctionSet() -> GapiPluginFunctionSet *;

NS_END()  // namespace global
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_GLOBAL_HPP
