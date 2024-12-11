#ifndef SWAY_RENDER_TEST_RASTERIZERSTATESTUB_HPP
#define SWAY_RENDER_TEST_RASTERIZERSTATESTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/idgenerator.hpp>

#include <gmock/gmock.h>  // MOCK_METHOD

NS_BEGIN_SWAY()
NS_BEGIN(render)

class RasterizerStateStub : public gapi::StateEnableable<gapi::RasterizerDescriptor> {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(RasterizerStateStub);

#pragma endregion

  MOCK_METHOD(gapi::RasterizerDescriptor, capture, (), (override));

  MOCK_METHOD(void, apply, (gapi::StateContext *, const gapi::RasterizerDescriptor &), (override));
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TEST_RASTERIZERSTATESTUB_HPP
