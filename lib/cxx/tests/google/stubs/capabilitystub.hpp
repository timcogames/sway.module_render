#ifndef SWAY_RENDER_TEST_CAPABILITYSTUB_HPP
#define SWAY_RENDER_TEST_CAPABILITYSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class CapabilityStub : public gapi::Capability {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(CapabilityStub);

#pragma endregion

  MOCK_METHOD(core::Version, getVersion, (), (const override));
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TEST_CAPABILITYSTUB_HPP
