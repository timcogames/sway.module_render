#ifndef SWAY_RENDER_RENDERSTATE_HPP
#define SWAY_RENDER_RENDERSTATE_HPP

#include <sway/render/_typedefs.hpp>

namespace sway::render {

class RenderState {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  RenderState();

  DTOR_DEFAULT(RenderState);

  /** @} */
#pragma endregion

  void restore();

  auto getContext() -> gapi::typedefs::StateContextPtr_t { return state_; }

private:
  gapi::typedefs::StateContextPtr_t state_;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_RENDERSTATE_HPP
