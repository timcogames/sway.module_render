#ifndef SWAY_RENDER_EXPERIENCE_COMMANDBUFFERDESCRIPTOR_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDBUFFERDESCRIPTOR_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup command
 * @{
 */

struct CommandBufferDescriptor {
  u32_t priority;
};

/**
 * end of command group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDBUFFERDESCRIPTOR_HPP
