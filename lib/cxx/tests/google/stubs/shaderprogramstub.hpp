#ifndef SWAY_RENDER_TEST_SHADERPROGRAMSTUB_HPP
#define SWAY_RENDER_TEST_SHADERPROGRAMSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class ShaderProgramStub : public gapi::ShaderProgram {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(ShaderProgramStub);

#pragma endregion

  MOCK_METHOD(void, attach, (gapi::typedefs::ShaderPtr_t), (override));

  MOCK_METHOD(void, detach, ((std::pair<gapi::ShaderType::Enum, gapi::typedefs::ShaderPtr_t>), bool), (override));

  MOCK_METHOD(gapi::typedefs::ShaderPtr_t, getShader, (gapi::ShaderType::Enum), (override));

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

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TEST_SHADERPROGRAMSTUB_HPP
