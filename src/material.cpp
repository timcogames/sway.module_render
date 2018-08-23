#include <sway/graphics/material.h>

#include <sway/gapi/gl/shader.h>
#include <sway/gapi/gl/shaderprogram.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Material::Material(const MaterialInitialInfo & info) {
	_shaderProgram = gapi::createShaderProgram();
	_shaderProgram->attach(gapi::createShader(info.vsoInfo));
	_shaderProgram->attach(gapi::createShader(info.fsoInfo));
	
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
