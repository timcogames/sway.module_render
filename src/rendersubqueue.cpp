#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/rendersubqueuegroups.h>
#include <sway/graphics/drawable.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

RenderSubqueue::RenderSubqueue()
	: _group(kRenderSubqueueGroup_Opaque) {
	// Empty
}

RenderSubqueue::RenderSubqueue(u32_t groupIdx)
	: _group(groupIdx) {
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

void RenderSubqueue::setGroupIdx(u32_t groupIdx) {
	_group = groupIdx;
}

u32_t RenderSubqueue::getGroupIdx() const {
	return _group;
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
