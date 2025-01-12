#ifndef SWAY_RENDER_TEST_VERTEXATTRIBLAYOUTSTUB_HPP
#define SWAY_RENDER_TEST_VERTEXATTRIBLAYOUTSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

namespace sway::render {

class VertexAttribLayoutStub : public gapi::VertexAttribLayout {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(VertexAttribLayoutStub);

#pragma endregion

  MOCK_METHOD(void, addAttribute, (gapi::VertexAttribDescriptor), (override));

  MOCK_METHOD(void, enable, (), (override));

  MOCK_METHOD(void, disable, (), (override));
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_VERTEXATTRIBLAYOUTSTUB_HPP
