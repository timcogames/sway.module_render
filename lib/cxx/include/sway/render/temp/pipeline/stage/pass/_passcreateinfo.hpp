#ifndef SWAY_RENDER_PASSCREATEINFO_HPP
#define SWAY_RENDER_PASSCREATEINFO_HPP

#include <sway/core.hpp>
#include <sway/render/temp/pipeline/_passactions.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

struct PassBufferInfo {
  PassAction::Enum action;
  u32_t clear;
};

struct PassCreateInfo {
  PassBufferInfo color;
  PassBufferInfo depth;
  PassBufferInfo stencil;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PASSCREATEINFO_HPP
