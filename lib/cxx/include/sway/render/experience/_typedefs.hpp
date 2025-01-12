#ifndef SWAY_RENDER_EXPERIENCE_TYPEDEFS_HPP
#define SWAY_RENDER_EXPERIENCE_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
NS_BEGIN(experience)

struct DeviceContext;
namespace DeviceContextTypedefs {
using Ptr_t = DeviceContext *;
}  // namespace DeviceContextTypedefs

struct RenderContext;
namespace RenderContextTypedefs {
using Ptr_t = RenderContext *;
}  // namespace RenderContextTypedefs

struct RenderModule;
namespace RenderModuleTypedefs {
using Ptr_t = RenderModule *;
using UniquePtr_t = std::unique_ptr<RenderModule>;
}  // namespace RenderModuleTypedefs

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_TYPEDEFS_HPP
