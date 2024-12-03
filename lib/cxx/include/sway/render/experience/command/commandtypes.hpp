#ifndef SWAY_RENDER_EXPERIENCE_COMMANDTYPES_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDTYPES_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

// clang-format off
DECLARE_ENUM(CommandType, 
  BEGIN_PASS,
  DRAW,
  END_PASS)
// clang-format on

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDTYPES_HPP
