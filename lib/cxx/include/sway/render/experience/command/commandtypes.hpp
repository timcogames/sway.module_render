#ifndef SWAY_RENDER_EXPERIENCE_COMMANDTYPES_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDTYPES_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

// clang-format off
#define COMMAND_TYPE_LIST(ITEM) \
  ITEM(BEGIN_PASS, 1) \
  ITEM(CLEAR, 2) \
  ITEM(BIND_PIPELINE, 3) \
  ITEM(DRAW, 4) \
  ITEM(END_PASS, 5)
// clang-format on

DECLARE_ENUM_U32(CommandType, COMMAND_TYPE_LIST)

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDTYPES_HPP
