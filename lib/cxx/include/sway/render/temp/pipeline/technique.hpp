#ifndef SWAY_RENDER_TECHNIQUE_HPP
#define SWAY_RENDER_TECHNIQUE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>

#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Technique {
  DECLARE_CLASS_POINTER_ALIASES(Technique)

public:
#pragma region "Ctors/Dtor"

  Technique() {}

  DTOR_VIRTUAL_DEFAULT(Technique);

#pragma endregion
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_TECHNIQUE_HPP
