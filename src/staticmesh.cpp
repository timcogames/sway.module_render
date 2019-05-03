#include <sway/graphics/staticmesh.h>
#include <sway/graphics/rendersubqueue.h>
#include <sway/graphics/drawable.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

StaticMesh::StaticMesh(RenderSubqueueRef_t subqueue, MaterialRef_t material, VertexDataRef_t vertexData, const gapi::BufferCreateInfoSet & infoSet) {
	auto drawable = std::make_shared<Drawable>(material, false);
	drawable->create(vertexData, infoSet);
	subqueue->addDrawable(drawable);
}

StaticMesh::~StaticMesh() {
	// Empty
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
