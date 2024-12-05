#ifndef SWAY_RENDER_EXPERIENCE_COMMANDQUEUETYPES_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDQUEUETYPES_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

DECLARE_ENUM(CommandQueueType, GRAPHICS, COMPUTE, COPY)

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDQUEUETYPES_HPP
