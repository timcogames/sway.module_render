#ifndef SWAY_RENDER_EXPERIENCE_PASSTYPES_HPP
#define SWAY_RENDER_EXPERIENCE_PASSTYPES_HPP

#include <sway/core.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup pass
 * @{
 */

// clang-format off
#define PASS_TYPE_LIST(ITEM) \
  ITEM(GRAPHICS, 1) \
  ITEM(COMPUTE, 2) \
  ITEM(RESOURCE, 3)
// clang-format on

DECLARE_ENUM_U32(PassType, PASS_TYPE_LIST)

/**
 * end of pass group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_PASSTYPES_HPP