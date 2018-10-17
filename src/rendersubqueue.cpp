#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/drawable.h>
#include <sway/graphics/material.h>
#include <sway/graphics/plugin.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderSubqueue::RenderSubqueue(RenderSubqueueGroup_t group)
	: _group(group) {
	_drawCall = Plugin::createDrawCall();
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

		_drawCall->execute(gapi::PrimitiveType_t::kTriangleList, currVBO->getCapacity(), NULL, Type_t::kNone);
		
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
