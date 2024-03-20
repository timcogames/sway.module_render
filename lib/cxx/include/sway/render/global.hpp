#ifndef SWAY_RENDER_GLOBAL_HPP
#define SWAY_RENDER_GLOBAL_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/idgenerator.hpp>

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

class ShaderProgramStub : public gapi::ShaderProgram {
public:
  virtual ~ShaderProgramStub() = default;

  MOCK_METHOD(void, attach, (gapi::ShaderPtr_t), (override));
  MOCK_METHOD(void, detach, ((std::pair<gapi::ShaderType, gapi::ShaderPtr_t>), bool), (override));
  MOCK_METHOD(gapi::ShaderPtr_t, getShader, (gapi::ShaderType), (override));
  MOCK_METHOD(void, link, (), (override));
  MOCK_METHOD(bool, isLinked, (), (const, override));
  MOCK_METHOD(void, validate, ());
  MOCK_METHOD(bool, isValidated, (), (const, override));
  MOCK_METHOD(void, use, (), (override));
  MOCK_METHOD(void, unuse, (), (override));
  MOCK_METHOD(bool, isUsed, (), (const, override));
  MOCK_METHOD(void, setUniformVec4f, (const std::string &, const math::vec4f_t &), (override));
  MOCK_METHOD(void, setUniformCol4f, (const std::string &, const math::col4f_t &), (override));
  MOCK_METHOD(void, setUniformMat4f, (const std::string &, const math::mat4f_t &), (override));
  MOCK_METHOD(void, setUniform1i, (const std::string &, s32_t), (override));
  MOCK_METHOD(void, setUniform1f, (const std::string &, f32_t), (override));
};

class ShaderStub : public gapi::Shader {
public:
  ShaderStub(gapi::ShaderType type)
      : gapi::Shader(type) {}

  virtual ~ShaderStub() = default;

  MOCK_METHOD(void, compile, (lpcstr_t), (override));
  MOCK_METHOD(bool, isCompiled, (), (const, override));
  MOCK_METHOD(s32_t, getAttribLocation, (std::optional<u32_t>, lpcstr_t), (override));
  MOCK_METHOD(gapi::ShaderType, getType, (), (const, override));
};

class IdGeneratorStub : public gapi::IdGenerator {
public:
  virtual ~IdGeneratorStub() = default;

  MOCK_METHOD(u32_t, newGuid, (), (override));
};

class VertexArrayStub : public gapi::VertexArray {
public:
  virtual ~VertexArrayStub() = default;

  MOCK_METHOD(void, bind, (), (override));
  MOCK_METHOD(void, unbind, (), (override));
};

class BufferStub : public gapi::Buffer {
public:
  BufferStub()
      : gapi::Buffer(gapi::BufferDescriptor()) {}

  virtual ~BufferStub() = default;

  MOCK_METHOD(bool, allocate, (const void *), (override));
  MOCK_METHOD(void, updateSubdata, (gapi::BufferSubdataDescriptor), (override));
  MOCK_METHOD(void, updateSubdata, (const void *), (override));
  MOCK_METHOD(void, flush, (s32_t, s32_t), (override));
  MOCK_METHOD(void *, map, (gapi::BufferMapAccess), (override));
  MOCK_METHOD(void *, mapRange, (s32_t, s32_t, core::detail::EnumClassBitset<gapi::BufferMapRangeAccess>), (override));
  MOCK_METHOD(void, unmap, (), (override));
  MOCK_METHOD(void, bindRange, (u32_t, ptrdiff_t, ptrdiff_t), (override));
  MOCK_METHOD(void, bind, (), (override));
  MOCK_METHOD(void, unbind, (), (override));
  MOCK_METHOD(gapi::BufferTarget, getTarget, (), (const, override));
  MOCK_METHOD(gapi::BufferUsage, getUsage, (), (const, override));
  MOCK_METHOD(s32_t, getCapacity, (), (const, override));
  MOCK_METHOD(s32_t, getByteStride, (), (const, override));
};

class VertexAttribLayoutStub : public gapi::VertexAttribLayout {
public:
  virtual ~VertexAttribLayoutStub() = default;

  MOCK_METHOD(void, addAttribute, (gapi::VertexAttribDescriptor), (override));
  MOCK_METHOD(void, enable, (), (override));
  MOCK_METHOD(void, disable, (), (override));
};

struct MockPluginFunctionSetInterface : public core::PluginFunctionSet {
  virtual ~MockPluginFunctionSetInterface() = default;

  PURE_VIRTUAL(auto createCapability()->gapi::CapabilityPtr_t);
  PURE_VIRTUAL(auto createShader(const gapi::ShaderCreateInfo &)->gapi::ShaderPtr_t);
  PURE_VIRTUAL(auto createShaderProgram()->gapi::ShaderProgramPtr_t);
  PURE_VIRTUAL(auto createIdGenerator()->gapi::IdGeneratorPtr_t);
  PURE_VIRTUAL(auto createBuffer(gapi::IdGeneratorPtr_t, const gapi::BufferCreateInfo &)->gapi::BufferPtr_t);
  PURE_VIRTUAL(auto createVertexArray()->gapi::VertexArrayPtr_t);
  PURE_VIRTUAL(auto createVertexAttribLayout(gapi::ShaderProgramPtr_t)->gapi::VertexAttribLayoutPtr_t);
  PURE_VIRTUAL(auto createTexture(const gapi::TextureCreateInfo &)->gapi::TexturePtr_t);
  PURE_VIRTUAL(auto createTextureSampler(gapi::TexturePtr_t)->gapi::TextureSamplerPtr_t);
  PURE_VIRTUAL(auto createDrawCall()->gapi::DrawCallPtr_t);
  PURE_VIRTUAL(auto createViewport()->gapi::ViewportPtr_t);
  PURE_VIRTUAL(auto createStateContext()->gapi::StateContextPtr_t);
};

struct MockPluginFunctionSet : public MockPluginFunctionSetInterface {
  virtual ~MockPluginFunctionSet() = default;

  MOCK_METHOD(gapi::CapabilityPtr_t, createCapability, (), (override));
  MOCK_METHOD(gapi::ShaderPtr_t, createShader, (const gapi::ShaderCreateInfo &), (override));
  MOCK_METHOD(gapi::ShaderProgramPtr_t, createShaderProgram, (), (override));
  MOCK_METHOD(gapi::IdGeneratorPtr_t, createIdGenerator, (), (override));
  MOCK_METHOD(gapi::BufferPtr_t, createBuffer, (gapi::IdGeneratorPtr_t, const gapi::BufferCreateInfo &), (override));
  MOCK_METHOD(gapi::VertexArrayPtr_t, createVertexArray, (), (override));
  MOCK_METHOD(gapi::VertexAttribLayoutPtr_t, createVertexAttribLayout, (gapi::ShaderProgramPtr_t), (override));
  MOCK_METHOD(gapi::TexturePtr_t, createTexture, (const gapi::TextureCreateInfo &), (override));
  MOCK_METHOD(gapi::TextureSamplerPtr_t, createTextureSampler, (gapi::TexturePtr_t), (override));
  MOCK_METHOD(gapi::DrawCallPtr_t, createDrawCall, (), (override));
  MOCK_METHOD(gapi::ViewportPtr_t, createViewport, (), (override));
  MOCK_METHOD(gapi::StateContextPtr_t, createStateContext, (), (override));
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
