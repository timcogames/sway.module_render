#ifndef SWAY_RENDER_SILHOUETTEPOSTPROCESSING_HPP
#define SWAY_RENDER_SILHOUETTEPOSTPROCESSING_HPP

#include <sway/core.hpp>
#include <sway/render/postprocessing.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class SilhouettePostProcessing : public PostProcessing {
public:
  SilhouettePostProcessing();

  ~SilhouettePostProcessing() = default;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_SILHOUETTEPOSTPROCESSING_HPP
