#include <sway/graphics/drawable.hpp>
#include <sway/graphics/primitives/quad.hpp>
#include <sway/graphics/rendersubqueue.hpp>
#include <sway/graphics/staticmesh.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

StaticMesh::StaticMesh(RenderSubqueueRef_t subqueue, VertexDataRef_t vtxdata, MaterialRef_t material) {
  gapi::BufferCreateInfoSet bufferCreateInfoSet;
  bufferCreateInfoSet.vb.desc.target = gapi::BufferTarget_t::Array;
  bufferCreateInfoSet.vb.desc.usage = gapi::BufferUsage_t::Static;
  bufferCreateInfoSet.vb.desc.byteStride = sizeof(math::VertexColor);
  bufferCreateInfoSet.vb.desc.capacity = vtxdata->getVertexCount();
  bufferCreateInfoSet.vb.data = vtxdata->getRaw();

  bufferCreateInfoSet.ib.desc.target = gapi::BufferTarget_t::ElementArray;
  bufferCreateInfoSet.ib.desc.usage = gapi::BufferUsage_t::Static;
  bufferCreateInfoSet.ib.desc.byteStride = sizeof(u32_t);
  bufferCreateInfoSet.ib.desc.capacity = vtxdata->getIndexCount();
  bufferCreateInfoSet.ib.data = vtxdata->getIndices().data();

  auto drawable = std::make_shared<Drawable>(material, true);
  drawable->create(vtxdata, bufferCreateInfoSet);
  subqueue->addDrawable(drawable);
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
