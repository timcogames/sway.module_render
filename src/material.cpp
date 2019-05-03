#include <sway/graphics/material.h>
#include <sway/graphics/rendersubsystem.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Material::Material(const gapi::ShaderCreateInfoSet & infoSet) {
	gapi::ConcreatePluginFunctionSet * pluginFuncSet = new gapi::ConcreatePluginFunctionSet();
	core::Plugin * plugin = getPluginInstance();
	if (plugin->isLoaded()) {
		plugin->initialize(pluginFuncSet);
	}

	_shaderProgram = pluginFuncSet->createShaderProgram();
	_shaderProgram->attach(pluginFuncSet->createShader(infoSet.vs));
	_shaderProgram->attach(pluginFuncSet->createShader(infoSet.fs));
	
	_shaderProgram->link();
	if (_shaderProgram->isLinked()) {
		// Empty
	}

	_shaderProgram->validate();
	if (_shaderProgram->isValidated()) {
		// Empty
	}
}

Material::~Material() {
	// Empty
}

void Material::loadFromXml() {
	// Empty
}

void Material::bind() {
	_shaderProgram->use();
}

void Material::unbind() {
	_shaderProgram->unuse();
}

gapi::ShaderProgramRef_t Material::getShaderProgram() {
	return _shaderProgram;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
