#include <sway/graphics/drawable.h>
#include <sway/graphics/vertexchannel.h>
#include <sway/graphics/vertexdata.h>
#include <sway/graphics/material.h>
#include <sway/graphics/rendersubsystem.h>

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

void Drawable::create(VertexDataRef_t vertexData, const gapi::BufferCreateInfoSet & infoSet) {
	auto pluginFuncSet = global::getGapiFunctionSet();

	_vlayout = pluginFuncSet->createVertexLayout(_material->getShaderProgram());
	for (const auto & channel : vertexData->getChannels())
		_vlayout->addAttribute(channel.second->getVertexAttribDescriptor());

	if (infoSet.vb.data != nullptr)
		_vbo = pluginFuncSet->createBuffer(infoSet.vb);

	if (infoSet.ib.data != nullptr && _indexed)
		_ibo = pluginFuncSet->createBuffer(infoSet.ib);
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
