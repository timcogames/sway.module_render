#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/drawable.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderSubqueue::RenderSubqueue(RenderSubqueueGroup_t group)
	: _group(group) {
	// Empty
}

RenderSubqueue::~RenderSubqueue() {
	// Empty
}

void RenderSubqueue::addDrawable(DrawableRef_t drawable) {
	_drawables.push_back(drawable);
}

void RenderSubqueue::render() {
	BOOST_FOREACH (DrawableRef_t drawable, _drawables) {
		// Empty
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
