#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/drawable.h>
#include <sway/graphics/material.h>
#include <sway/graphics/rendersubsystem.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderSubqueue::RenderSubqueue(RenderSubqueueGroup_t group)
	: _group(group) {
	gapi::ConcreatePluginFunctionSet * pluginFuncSet = new gapi::ConcreatePluginFunctionSet();
	core::Plugin * plugin = getPluginInstance();
	if (plugin->isLoaded()) {
		plugin->initialize(pluginFuncSet);
	}

	_drawCall = pluginFuncSet->createDrawCall();
}

RenderSubqueue::~RenderSubqueue() {
	// Empty
}

void RenderSubqueue::addDrawable(DrawableRef_t drawable) {
	_drawables.push_back(drawable);
}

void RenderSubqueue::render() {
	gapi::BufferRef_t currVBO = nullptr, currIBO = nullptr;

	BOOST_FOREACH (DrawableRef_t drawable, _drawables) {
		currVBO = drawable->getVBO();
		currIBO = drawable->getIBO();

		drawable->getMaterial()->bind();

		currVBO->bind();
		drawable->getVertexLayout()->enable();

		if (_drawCall)
			_drawCall->execute(gapi::PrimitiveType_t::kTriangleList, currVBO->getCapacity(), NULL, core::detail::DataType_t::kChar);
		
		drawable->getVertexLayout()->disable();
		currVBO->unbind();

		drawable->getMaterial()->unbind();
	}
}

void RenderSubqueue::setGroup(RenderSubqueueGroup_t group) {
	_group = group;
}

RenderSubqueueGroup_t RenderSubqueue::getGroup() const {
	return _group;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
