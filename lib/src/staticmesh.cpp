#include <sway/graphics/drawable.hpp>
#include <sway/graphics/primitives/quad.hpp>
#include <sway/graphics/rendersubqueue.hpp>
#include <sway/graphics/staticmesh.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

StaticMesh::StaticMesh(RenderSubqueueRef_t subqueue, MaterialRef_t material) {
  _vertexData = std::make_shared<primitives::Quad>(1, 1);

  gapi::BufferCreateInfoSet bufferCreateInfoSet;
  bufferCreateInfoSet.vb.desc.target = gapi::BufferTarget_t::kArray;
  bufferCreateInfoSet.vb.desc.usage = gapi::BufferUsage_t::kStatic;
  bufferCreateInfoSet.vb.desc.byteStride = sizeof(math::VertexColor);
  bufferCreateInfoSet.vb.desc.capacity = _vertexData->getVertexCount();
  bufferCreateInfoSet.vb.data = _vertexData->getRaw();

  bufferCreateInfoSet.ib.desc.target = gapi::BufferTarget_t::kElementArray;
  bufferCreateInfoSet.ib.desc.usage = gapi::BufferUsage_t::kStatic;
  bufferCreateInfoSet.ib.desc.byteStride = sizeof(u32_t);
  bufferCreateInfoSet.ib.desc.capacity = _vertexData->getIndexCount();
  bufferCreateInfoSet.ib.data = _vertexData->getIndices().data();

  auto drawable = std::make_shared<Drawable>(material, true);
  drawable->create(_vertexData, bufferCreateInfoSet);
  subqueue->addDrawable(drawable);
}

StaticMesh::~StaticMesh() {
  // Empty
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
