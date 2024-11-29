#ifndef SWAY_RENDER_EXPERIENCE_STAGE_HPP
#define SWAY_RENDER_EXPERIENCE_STAGE_HPP

#include <sway/render/experience/stage/_typedefs.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Stage : public core::misc::Enableable {
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
