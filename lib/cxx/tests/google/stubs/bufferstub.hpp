#ifndef SWAY_RENDER_TEST_BUFFERSTUB_HPP
#define SWAY_RENDER_TEST_BUFFERSTUB_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <gmock/gmock.h>

namespace sway::render {

class BufferStub : public gapi::Buffer {
public:
#pragma region "Ctors/Dtor"

  BufferStub()
      : gapi::Buffer(gapi::BufferDescriptor()) {}

  DTOR_VIRTUAL_DEFAULT(BufferStub);

#pragma endregion

  MOCK_METHOD(bool, allocate, (const void *), (override));

  MOCK_METHOD(void, updateSubdata, (gapi::BufferSubdataDescriptor), (override));

  MOCK_METHOD(void, updateSubdata, (const void *), (override));

  MOCK_METHOD(void, flush, (i32_t, i32_t), (override));

  MOCK_METHOD(void *, map, (gapi::BufferMapAccess::Enum), (override));

  MOCK_METHOD(void *, mapRange, (i32_t, i32_t, core::EnumClassBitset<gapi::BufferMapRangeAccess::Enum>), (override));

  MOCK_METHOD(void, unmap, (), (override));

  MOCK_METHOD(void, bindRange, (u32_t, ptrdiff_t, ptrdiff_t), (override));

  MOCK_METHOD(void, bind, (), (override));

  MOCK_METHOD(void, unbind, (), (override));

  MOCK_METHOD(gapi::BufferTarget::Enum, getTarget, (), (const, override));

  MOCK_METHOD(gapi::BufferUsage::Enum, getUsage, (), (const, override));

  MOCK_METHOD(i32_t, getCapacity, (), (const, override));

  MOCK_METHOD(i32_t, getByteStride, (), (const, override));
};

}  // namespace sway::render

#endif  // SWAY_RENDER_TEST_BUFFERSTUB_HPP
