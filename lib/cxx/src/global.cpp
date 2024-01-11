#include <sway/render/global.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(global)

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

NAMESPACE_END(global)
NAMESPACE_END(render)
NAMESPACE_END(sway)
