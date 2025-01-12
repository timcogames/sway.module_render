#ifndef SWAY_RENDER_EXPERIENCE_PIPELINE_HPP
#define SWAY_RENDER_EXPERIENCE_PIPELINE_HPP

#include <sway/render/_stdafx.hpp>

namespace sway::render {
NS_BEGIN(experience)

/**
 * @addtogroup pipeline
 * @{
 */

class Pipeline {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Pipeline();

  DTOR_DEFAULT(Pipeline);

  /** @} */
#pragma endregion
};

/**
 * end of pipeline group
 * @}
 */

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_PIPELINE_HPP
