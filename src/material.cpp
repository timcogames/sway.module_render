#include <sway/graphics/material.h>
#include <sway/graphics/plugin.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Material::Material(const gapi::ShaderCreateInfoSet & infoSet) {
	_shaderProgram = Plugin::createShaderProgram();
	_shaderProgram->attach(Plugin::createShader(infoSet.vs));
	_shaderProgram->attach(Plugin::createShader(infoSet.fs));
	
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
