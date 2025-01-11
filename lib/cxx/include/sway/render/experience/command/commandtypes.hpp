#ifndef SWAY_RENDER_EXPERIENCE_COMMANDTYPES_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDTYPES_HPP

#include <sway/render/_stdafx.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

// clang-format off
DECLARE_ENUM(CommandType, 
  BEGIN_PASS, 
  CLEAR, 
  BIND_PIPELINE, 
  DRAW, 
  END_PASS)
// clang-format on

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDTYPES_HPP
