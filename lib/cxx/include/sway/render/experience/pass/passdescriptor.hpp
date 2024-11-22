#ifndef SWAY_RENDER_EXPERIENCE_PASSDESCRIPTOR_HPP
#define SWAY_RENDER_EXPERIENCE_PASSDESCRIPTOR_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct PassDescriptor {
  u32_t format;

  auto hashValue() const -> std::size_t {
    std::size_t hash{0};
    sway::core::misc::hashCombine(hash, format);
    return hash;
  }
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PASSDESCRIPTOR_HPP
