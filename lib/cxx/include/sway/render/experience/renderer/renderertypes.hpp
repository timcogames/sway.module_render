#ifndef SWAY_RENDER_EXPERIENCE_RENDERERTYPES_HPP
#define SWAY_RENDER_EXPERIENCE_RENDERERTYPES_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
NS_BEGIN(experience)

// clang-format off
#define RENDERER_TYPE_LIST(ITEM) \
  ITEM(IDX_FWD, 0) \
  ITEM(IDX_DEF, 1)
// clang-format on

DECLARE_ENUM_IDX(RendererType, RENDERER_TYPE_LIST)

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_RENDERERTYPES_HPP
