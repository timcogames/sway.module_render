#ifndef SWAY_RENDER_EXPERIENCE_STAGE_HPP
#define SWAY_RENDER_EXPERIENCE_STAGE_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/experience/stage/_typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Stage : public core::Enableable {
public:
#pragma region "Ctors/Dtor"

  Stage() {}

  DTOR_VIRTUAL_DEFAULT(Stage);

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_STAGE_HPP
