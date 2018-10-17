#include <sway/graphics/staticmesh.h>
#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/drawable.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

StaticMesh::StaticMesh(RenderSubqueueRef_t subqueue, MaterialRef_t material, const gapi::BufferCreateInfoSet & infoSet) {
	auto drawable = boost::make_shared<Drawable>(material, false);
	drawable->create(infoSet);
	subqueue->addDrawable(drawable);
}

StaticMesh::~StaticMesh() {
	// Empty
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
