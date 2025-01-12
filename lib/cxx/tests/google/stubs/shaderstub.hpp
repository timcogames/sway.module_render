#ifndef SWAY_RENDER_TEST_SHADERSTUB_HPP
#define SWAY_RENDER_TEST_SHADERSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

namespace sway::render {

class ShaderStub : public gapi::Shader {
public:
#pragma region "Ctors/Dtor"

  ShaderStub(gapi::ShaderType::Enum type)
      : gapi::Shader(type) {}

  DTOR_VIRTUAL_DEFAULT(ShaderStub);

#pragma endregion

  MOCK_METHOD(void, compile, (lpcstr_t), (override));

  MOCK_METHOD(bool, isCompiled, (), (const, override));

  MOCK_METHOD(i32_t, getAttribLocation, (std::optional<u32_t>, lpcstr_t), (override));

  MOCK_METHOD(gapi::ShaderType::Enum, getType, (), (const, override));
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_SHADERSTUB_HPP
