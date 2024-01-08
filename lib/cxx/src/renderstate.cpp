#include <sway/render/global.hpp>
#include <sway/render/renderstate.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

RenderState::RenderState() { state_ = global::getGapiFunctionSet()->createStateContext(); }

void RenderState::restore() {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
