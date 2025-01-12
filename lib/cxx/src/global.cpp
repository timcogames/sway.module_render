#include <sway/render/global.hpp>

namespace sway::render {
NS_BEGIN(global)

#ifdef RENDER_USE_GMOCK

core::Plugin *pluginInstance_ = nullptr;
MockPluginFunctionSet *pluginFunctionSet_ = nullptr;

auto getGapiPluginFunctionSet() -> MockPluginFunctionSet * {
  if (pluginFunctionSet_ == nullptr) {
    pluginFunctionSet_ = new MockPluginFunctionSet();
  }

  return pluginFunctionSet_;
}

#else

core::Plugin *pluginInstance_ = nullptr;
gapi::ConcreatePluginFunctionSet *pluginFunctionSet_ = nullptr;

auto getGapiPluginFunctionSet() -> gapi::ConcreatePluginFunctionSet * {
  if (pluginFunctionSet_ == nullptr) {
    pluginInstance_->initialize(pluginFunctionSet_ = new gapi::ConcreatePluginFunctionSet());
  }

  return pluginFunctionSet_;
}

#endif

NS_END()  // namespace global
}  // namespace sway::render
