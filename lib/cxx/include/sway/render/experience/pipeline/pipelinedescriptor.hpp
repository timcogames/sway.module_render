#ifndef SWAY_RENDER_EXPERIENCE_PIPELINEDESCRIPTOR_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINEDESCRIPTOR_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

struct PipelineDescriptor {
  u32_t type;

  auto hashValue() const -> std::size_t {
    std::size_t hash{0};
    core::misc::hashCombine(hash, type);
    return hash;
  }
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINEDESCRIPTOR_HPP
