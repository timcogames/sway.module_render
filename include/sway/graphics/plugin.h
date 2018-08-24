#ifndef SWAY_GRAPHICS_PLUGIN_H
#define SWAY_GRAPHICS_PLUGIN_H

#include <sway/graphics/plugindescriptor.h>
#include <sway/graphics/prereqs.h>
#include <dlfcn.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Plugin {
public:
	static bool open(const PluginDescriptor & desc);
	static void close(void * handle);

	static gapi::CreateCapabilityFunc_t createCapability;
	static gapi::CreateShaderFunc_t createShader;
	static gapi::CreateShaderProgramFunc_t createShaderProgram;
	static gapi::CreateBufferFunc_t createBuffer;
	static gapi::CreateVertexLayoutFunc_t createVertexLayout;
	static gapi::CreateDrawCallFunc_t createDrawCall;
	static gapi::CreateViewportFunc_t createViewport;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif // SWAY_GRAPHICS_PLUGIN_H
