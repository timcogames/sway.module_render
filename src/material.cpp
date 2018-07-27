#include <sway/graphics/material.h>

#include <sway/gapi/gl/shaderobject.h>
#include <sway/gapi/gl/shaderprogram.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Material::Material(const MaterialInitialInfo & info) {
	_shader = new gapi::ShaderProgram();
	_shader->attach(gapi::ShaderObject::create(info.vsoInfo));
	_shader->attach(gapi::ShaderObject::create(info.fsoInfo));
	
	_shader->link();
	if (_shader->isLinked()) {
		// Empty
	}

	_shader->validate();
	if (_shader->isValidated()) {
		// Empty
	}
}

Material::~Material() {
	SAFE_DELETE(_shader);
}

void Material::bind() {
	_shader->use();
}

void Material::unbind() {
	_shader->unuse();
}

gapi::IShaderProgramBase * Material::getShader() {
	return _shader;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
