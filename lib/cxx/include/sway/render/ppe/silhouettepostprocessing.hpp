#ifndef SWAY_RENDER_PPE_SILHOUETTEPOSTPROCESSING_HPP
#define SWAY_RENDER_PPE_SILHOUETTEPOSTPROCESSING_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/ppe/postprocessing.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class SilhouettePostProcessing : public PostProcessing {
public:
  SilhouettePostProcessing(gapi::ViewportPtr_t viewport)
      : PostProcessing(viewport) {}

  ~SilhouettePostProcessing() = default;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PPE_SILHOUETTEPOSTPROCESSING_HPP
