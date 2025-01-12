#ifndef SWAY_RENDER_TEST_TEXTUREIDGENERATORSTUB_HPP
#define SWAY_RENDER_TEST_TEXTUREIDGENERATORSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/idgenerator.hpp>

#include <gmock/gmock.h>  // MOCK_METHOD

namespace sway::render {

class TextureIdGeneratorStub : public gapi::IdGenerator {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(TextureIdGeneratorStub);

#pragma endregion

  MOCK_METHOD(u32_t, getNextUid, (), (override));
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_TEXTUREIDGENERATORSTUB_HPP
