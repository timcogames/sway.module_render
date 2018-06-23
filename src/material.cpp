#include <sway/graphics/material.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Material::Material(const MaterialInitialInfo & info) {
	_shaderProgram = new gapi::ShaderProgram();
	_shaderProgram->attach(gapi::ShaderObject::create(info.vsoInfo));
	_shaderProgram->attach(gapi::ShaderObject::create(info.fsoInfo));
	
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
	SAFE_DELETE(_shaderProgram);
}

void Material::bind() {
	_shaderProgram->use();
}

void Material::unbind() {
	_shaderProgram->unuse();
}

gapi::ShaderProgram * Material::getShaderProgram() {
	return _shaderProgram;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
