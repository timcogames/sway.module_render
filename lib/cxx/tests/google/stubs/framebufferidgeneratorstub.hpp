#ifndef SWAY_RENDER_TEST_FRAMEBUFFERIDGENERATORSTUB_HPP
#define SWAY_RENDER_TEST_FRAMEBUFFERIDGENERATORSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/idgenerator.hpp>

#include <gmock/gmock.h>  // MOCK_METHOD

NS_BEGIN_SWAY()
NS_BEGIN(render)

class FrameBufferIdGeneratorStub : public gapi::IdGenerator {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(FrameBufferIdGeneratorStub);

#pragma endregion

  MOCK_METHOD(u32_t, getNextUid, (), (override));
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TEST_FRAMEBUFFERIDGENERATORSTUB_HPP
