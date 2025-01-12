#ifndef SWAY_RENDER_PPE_SILHOUETTEPOSTPROCESSING_HPP
#define SWAY_RENDER_PPE_SILHOUETTEPOSTPROCESSING_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/ppe/postprocessing.hpp>

namespace sway::render {

class SilhouettePostProcessing : public PostProcessing {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  SilhouettePostProcessing(gapi::typedefs::ViewportPtr_t viewport)
      : PostProcessing(viewport) {}

  ~SilhouettePostProcessing() = default;

  /** @} */
#pragma endregion
};

}  // namespace sway::render

#endif  // SWAY_RENDER_PPE_SILHOUETTEPOSTPROCESSING_HPP
