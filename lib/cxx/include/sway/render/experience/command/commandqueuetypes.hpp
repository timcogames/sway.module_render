#ifndef SWAY_RENDER_EXPERIENCE_COMMANDQUEUETYPES_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDQUEUETYPES_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
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
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDQUEUETYPES_HPP
