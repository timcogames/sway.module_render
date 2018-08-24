#include <sway/graphics/plugin.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

gapi::CreateCapabilityFunc_t Plugin::createCapability = NULL;
gapi::CreateShaderFunc_t Plugin::createShader = NULL;
gapi::CreateShaderProgramFunc_t Plugin::createShaderProgram = NULL;
gapi::CreateBufferFunc_t Plugin::createBuffer = NULL;
gapi::CreateVertexLayoutFunc_t Plugin::createVertexLayout = NULL;
gapi::CreateDrawCallFunc_t Plugin::createDrawCall = NULL;
gapi::CreateViewportFunc_t Plugin::createViewport = NULL;

bool Plugin::open(const PluginDescriptor & desc) {
	char * error;
	void * handle = dlopen(desc.fullname.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!handle) {
		fprintf(stderr, "Cannot load plugin %s\n%s\n", desc.fullname.c_str(), dlerror());
		return false;
	}

	dlerror();

	createCapability = (core::binding::ProcAddress_t) dlsym(handle, "createCapability");
	if ((error = dlerror ()) != NULL) {
		dlclose(handle);
		fprintf(stderr, "Cannot find %s in plugin %s\n%s\n", "createCapability", desc.fullname.c_str(), error);
		return false;
	}
	
	createShader = (core::binding::ProcAddress_t) dlsym(handle, "createShader");
	if ((error = dlerror ()) != NULL) {
		dlclose(handle);
		fprintf(stderr, "Cannot find %s in plugin %s\n%s\n", "createShader", desc.fullname.c_str(), error);
		return false;
	}

	createShaderProgram = (core::binding::ProcAddress_t) dlsym(handle, "createShaderProgram");
	if ((error = dlerror ()) != NULL) {
		dlclose(handle);
		fprintf(stderr, "Cannot find %s in plugin %s\n%s\n", "createShaderProgram", desc.fullname.c_str(), error);
		return false;
	}

	createBuffer = (core::binding::ProcAddress_t) dlsym(handle, "createBuffer");
	if ((error = dlerror ()) != NULL) {
		dlclose(handle);
		fprintf(stderr, "Cannot find %s in plugin %s\n%s\n", "createBuffer", desc.fullname.c_str(), error);
		return false;
	}

	createVertexLayout = (core::binding::ProcAddress_t) dlsym(handle, "createVertexLayout");
	if ((error = dlerror ()) != NULL) {
		dlclose(handle);
		fprintf(stderr, "Cannot find %s in plugin %s\n%s\n", "createVertexLayout", desc.fullname.c_str(), error);
		return false;
	}

	createDrawCall = (core::binding::ProcAddress_t) dlsym(handle, "createDrawCall");
	if ((error = dlerror ()) != NULL) {
		dlclose(handle);
		fprintf(stderr, "Cannot find %s in plugin %s\n%s\n", "createDrawCall", desc.fullname.c_str(), error);
		return false;
	}

	createViewport = (core::binding::ProcAddress_t) dlsym(handle, "createViewport");
	if ((error = dlerror ()) != NULL) {
		dlclose(handle);
		fprintf(stderr, "Cannot find %s in plugin %s\n%s\n", "createViewport", desc.fullname.c_str(), error);
		return false;
	}

	return true;
}

void Plugin::close(void * handle) {
	dlclose(handle);
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
