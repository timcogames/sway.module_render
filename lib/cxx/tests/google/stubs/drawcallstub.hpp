#ifndef SWAY_RENDER_TEST_DRAWCALLSTUB_HPP
#define SWAY_RENDER_TEST_DRAWCALLSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class DrawCallStub : public gapi::DrawCall {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(DrawCallStub);

#pragma endregion

  MOCK_METHOD(void, execute, (gapi::TopologyType::Enum, gapi::BufferSet, core::ValueDataType::Enum), (override));
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TEST_DRAWCALLSTUB_HPP
