#ifndef SWAY_RENDER_TEST_IDGENERATORSTUB_HPP
#define SWAY_RENDER_TEST_IDGENERATORSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/idgenerator.hpp>

#include <gmock/gmock.h>

namespace sway::render {

class IdGeneratorStub : public gapi::IdGenerator {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(IdGeneratorStub);

#pragma endregion

  MOCK_METHOD(u32_t, getNextUid, (), (override));
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_IDGENERATORSTUB_HPP
