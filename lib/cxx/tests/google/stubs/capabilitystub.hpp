#ifndef SWAY_RENDER_TEST_CAPABILITYSTUB_HPP
#define SWAY_RENDER_TEST_CAPABILITYSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

namespace sway::render {

class CapabilityStub : public gapi::Capability {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(CapabilityStub);

#pragma endregion

  MOCK_METHOD(core::Version, getVersion, (), (const override));
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_CAPABILITYSTUB_HPP
