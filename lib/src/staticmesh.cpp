#include <sway/graphics/drawable.hpp>
#include <sway/graphics/primitives/quad.hpp>
#include <sway/graphics/rendersubqueue.hpp>
#include <sway/graphics/staticmesh.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

StaticMesh::StaticMesh(RenderSubqueueRef_t subqueue, MaterialRef_t material) {
  vertexData_ = std::make_shared<primitives::Quad>(0.5, 0.5);

  gapi::BufferCreateInfoSet bufferCreateInfoSet;
  bufferCreateInfoSet.vb.desc.target = gapi::BufferTarget_t::kArray;
  bufferCreateInfoSet.vb.desc.usage = gapi::BufferUsage_t::kStatic;
  bufferCreateInfoSet.vb.desc.byteStride = sizeof(math::VertexColor);
  bufferCreateInfoSet.vb.desc.capacity = vertexData_->getVertexCount();
  bufferCreateInfoSet.vb.data = vertexData_->getRaw();

  bufferCreateInfoSet.ib.desc.target = gapi::BufferTarget_t::kElementArray;
  bufferCreateInfoSet.ib.desc.usage = gapi::BufferUsage_t::kStatic;
  bufferCreateInfoSet.ib.desc.byteStride = sizeof(u32_t);
  bufferCreateInfoSet.ib.desc.capacity = vertexData_->getIndexCount();
  bufferCreateInfoSet.ib.data = vertexData_->getIndices().data();

  auto drawable = std::make_shared<Drawable>(material, true);
  drawable->create(vertexData_, bufferCreateInfoSet);
  subqueue->addDrawable(drawable);
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
