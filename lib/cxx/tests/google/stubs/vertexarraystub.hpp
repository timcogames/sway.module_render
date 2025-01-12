#ifndef SWAY_RENDER_TEST_VERTEXARRAYSTUB_HPP
#define SWAY_RENDER_TEST_VERTEXARRAYSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

namespace sway::render {

class VertexArrayStub : public gapi::VertexArray {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(VertexArrayStub);

#pragma endregion

  MOCK_METHOD(void, bind, (), (override));

  MOCK_METHOD(void, unbind, (), (override));
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_VERTEXARRAYSTUB_HPP
