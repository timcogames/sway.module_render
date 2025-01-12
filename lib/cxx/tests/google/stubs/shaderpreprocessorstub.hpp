#ifndef SWAY_RENDER_TEST_SHADERPREPROCESSORSTUB_HPP
#define SWAY_RENDER_TEST_SHADERPREPROCESSORSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

namespace sway::render {

class ShaderPreprocessorStub : public gapi::ShaderPreprocessor {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(ShaderPreprocessorStub);

#pragma endregion

  MOCK_METHOD(void, addDefine, (const std::string &name, const std::string &val), (override));

  MOCK_METHOD(bool, hasDefined, (const std::string &name), (const override));
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_SHADERPREPROCESSORSTUB_HPP
