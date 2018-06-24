#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/drawable.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderSubqueue::RenderSubqueue(u32_t groupIdx) {
	setGroupIdx(groupIdx);
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

void RenderSubqueue::setGroupIdx(u32_t groupIdx) {
	if (groupIdx > RENDER_SUBQUEUE_GROUP_COUNT)
		throw ArgumentException("groupIdx");

	_group = groupIdx;
}

u32_t RenderSubqueue::getGroupIdx() const {
	return _group;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
