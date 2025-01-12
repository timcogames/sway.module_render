#ifndef SWAY_RENDER_EXPERIENCE_PASSTYPES_HPP
#define SWAY_RENDER_EXPERIENCE_PASSTYPES_HPP

#include <sway/core.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup pass
 * @{
 */

DECLARE_ENUM(PassType, GRAPHICS, COMPUTE, RESOURCE)

/**
 * end of pass group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_PASSTYPES_HPP