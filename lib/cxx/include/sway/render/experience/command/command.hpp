#ifndef SWAY_RENDER_EXPERIENCE_COMMAND_HPP
#define SWAY_RENDER_EXPERIENCE_COMMAND_HPP

#include <sway/render/experience/command/_typedefs.hpp>
#include <sway/render/experience/command/commandtypes.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct Command {
  CommandType::Enum type;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMAND_HPP
