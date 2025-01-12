#include <sway/render/global.hpp>
#include <sway/render/renderstate.hpp>

namespace sway::render {

RenderState::RenderState() { state_ = global::getGapiPluginFunctionSet()->createStateContext(); }

void RenderState::restore() {}

}  // namespace sway::render
