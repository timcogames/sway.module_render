#ifndef SWAY_RENDER_TEST_VERTEXATTRIBLAYOUTSTUB_HPP
#define SWAY_RENDER_TEST_VERTEXATTRIBLAYOUTSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class VertexAttribLayoutStub : public gapi::VertexAttribLayout {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(VertexAttribLayoutStub);

#pragma endregion

  MOCK_METHOD(void, addAttribute, (gapi::VertexAttribDescriptor), (override));

  MOCK_METHOD(void, enable, (), (override));

  MOCK_METHOD(void, disable, (), (override));
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TEST_VERTEXATTRIBLAYOUTSTUB_HPP
