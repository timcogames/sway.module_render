#ifndef SWAY_RENDER_EXPERIENCE_COMMANDBUFFERDESCRIPTOR_HPP
#define SWAY_RENDER_EXPERIENCE_COMMANDBUFFERDESCRIPTOR_HPP

#include <sway/render/_stdafx.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
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
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_COMMANDBUFFERDESCRIPTOR_HPP
