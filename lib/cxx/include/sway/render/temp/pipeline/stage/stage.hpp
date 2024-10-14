#ifndef SWAY_RENDER_STAGE_HPP
#define SWAY_RENDER_STAGE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/temp/pipeline/stage/pass/passqueue.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Stage : public PassQueue {
  DECLARE_PTR_ALIASES(Stage)
  DECLARE_PTR_VECTOR(Stage, SharedPtr)

public:
#pragma region "Ctors/Dtor"

  Stage() {}

  DTOR_VIRTUAL_DEFAULT(Stage);

#pragma endregion

private:
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_STAGE_HPP
