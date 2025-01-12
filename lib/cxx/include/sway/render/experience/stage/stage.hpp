#ifndef SWAY_RENDER_EXPERIENCE_STAGE_HPP
#define SWAY_RENDER_EXPERIENCE_STAGE_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/stage/_typedefs.hpp>

namespace sway::render {
NS_BEGIN(experience)

class Stage : public core::Enableable {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Stage() {}

  DTOR_VIRTUAL_DEFAULT(Stage);

  /** @} */
#pragma endregion
};

NS_END()  // namespace experience
}  // namespace sway::render

#endif  // SWAY_RENDER_EXPERIENCE_STAGE_HPP
