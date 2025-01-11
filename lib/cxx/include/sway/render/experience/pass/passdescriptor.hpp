#ifndef SWAY_RENDER_EXPERIENCE_PASSDESCRIPTOR_HPP
#define SWAY_RENDER_EXPERIENCE_PASSDESCRIPTOR_HPP

#include <sway/render/_stdafx.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

/**
 * @addtogroup pass
 * @{
 */

struct PassDescriptor {
  u32_t format;

  auto hashValue() const -> std::size_t {
    std::size_t hash{0};
    core::hashCombine(hash, format);
    return hash;
  }
};

/**
 * end of pass group
 * @}
 */

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PASSDESCRIPTOR_HPP
