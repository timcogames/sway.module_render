#include <sway/graphics/staticmesh.h>
#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/drawable.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

StaticMesh::StaticMesh(RenderSubqueueRef_t subqueue) {
	subqueue->addDrawable(boost::make_shared<Drawable>());
}

StaticMesh::~StaticMesh() {
	// Empty
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
