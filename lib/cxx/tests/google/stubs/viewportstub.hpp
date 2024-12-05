#ifndef SWAY_RENDER_TEST_VIEWPORTSTUB_H
#define SWAY_RENDER_TEST_VIEWPORTSTUB_H

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class ViewportStub : public gapi::Viewport {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(ViewportStub);

#pragma endregion

  MOCK_METHOD(void, set, (i32_t, i32_t, i32_t, i32_t), (override));

  MOCK_METHOD(void, set, (i32_t, i32_t), (override));

  MOCK_METHOD(math::rect4i_t, get, (), (const override));

  MOCK_METHOD(f32_t, aspect, (), (const override));

  MOCK_METHOD(void, setClearColor, (const math::col4f_t &), (override));

  MOCK_METHOD(void, clear, (gapi::ClearFlag), (override));
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TEST_VIEWPORTSTUB_H
