#include <sway/render/global.hpp>
#include <sway/render/renderstate.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

RenderState::RenderState() { state_ = global::getGapiPluginFunctionSet()->createStateContext(); }

void RenderState::restore() {}

NS_END()  // namespace render
NS_END()  // namespace sway
