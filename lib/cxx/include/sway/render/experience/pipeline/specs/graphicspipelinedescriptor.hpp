#ifndef SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINEDESCRIPTOR_HPP
#define SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINEDESCRIPTOR_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

class CacheableBase {
public:
  PURE_VIRTUAL(auto getHash() const -> std::size_t);
};

struct GraphicsPipelineDescriptor : public CacheableBase {
  std::array<std::optional<std::string>, 3> shaders;  ///< VERT, FRAG, GEOM
  u32_t topology;

  MTHD_OVERRIDE(auto getHash() const -> std::size_t) {
    std::size_t hash{0};
    for (const auto &shader : shaders) {
      core::hashCombine(hash, shader.value_or("(null)"));
    }

    core::hashCombine(hash, topology);

    return hash;
  }
};

/**
 * end of pipeline group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_GRAPHICSPIPELINEDESCRIPTOR_HPP
