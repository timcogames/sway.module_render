#include <sway/graphics/drawable.h>
#include <sway/graphics/material.h>
#include <sway/graphics/plugin.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Drawable::Drawable(MaterialRef_t material, bool indexed)
	: _vbo(nullptr)
	, _ibo(nullptr)
	, _vlayout(nullptr)
	, _material(material)
	, _indexed(indexed) {
	// Empty
}

Drawable::~Drawable() {
	// Empty
}

void Drawable::create(const gapi::BufferCreateInfoSet & infoSet) {
	_vbo = Plugin::createBuffer(infoSet.vb);

	if (_indexed)
		_ibo = Plugin::createBuffer(infoSet.ib);

	_vlayout = Plugin::createVertexLayout(_material->getShaderProgram());
	_vlayout->addAttribute(gapi::VertexAttribute::merge<math::vec3f_t>(gapi::VertexSemantic_t::kPosition, false, true));
}

gapi::BufferRef_t Drawable::getVBO() {
	return _vbo;
}

gapi::BufferRef_t Drawable::getIBO() {
	return _ibo;
}

gapi::VertexLayoutRef_t Drawable::getVertexLayout() {
	return _vlayout;
}

MaterialRef_t Drawable::getMaterial() {
	return _material;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
