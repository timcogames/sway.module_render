#ifndef SWAY_RENDER_PPE_SILHOUETTEPOSTPROCESSING_HPP
#define SWAY_RENDER_PPE_SILHOUETTEPOSTPROCESSING_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/ppe/postprocessing.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class SilhouettePostProcessing : public PostProcessing {
public:
  SilhouettePostProcessing(gapi::ViewportPtr_t viewport)
      : PostProcessing(viewport) {}

  ~SilhouettePostProcessing() = default;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PPE_SILHOUETTEPOSTPROCESSING_HPP
