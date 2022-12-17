#include <sway/graphics/drawable.hpp>
#include <sway/graphics/geometrycreateinfo.hpp>
#include <sway/graphics/primitives/quad.hpp>
#include <sway/graphics/rendersubqueue.hpp>
#include <sway/graphics/staticmesh.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

StaticMesh::StaticMesh(RenderSubqueueRef_t subqueue, VertexDataRef_t vtxdata, MaterialRef_t material) {
  GeometryCreateInfo info;

  info.vb.desc.target = gapi::BufferTarget::ARRAY;
  info.vb.desc.usage = gapi::BufferUsage::STATIC;
  info.vb.desc.byteStride = sizeof(math::VertexColor);
  info.vb.desc.capacity = vtxdata->getVertexCount();
  info.vb.data = vtxdata->getRaw();

  info.ib.desc.target = gapi::BufferTarget::ELEMENT_ARRAY;
  info.ib.desc.usage = gapi::BufferUsage::STATIC;
  info.ib.desc.byteStride = sizeof(u32_t);
  info.ib.desc.capacity = vtxdata->getIndexCount();
  info.ib.data = vtxdata->getIndices().data();

  info.topology = gapi::TopologyType::TRIANGLE_LIST;

  auto indexed = true;
  auto drawable = std::make_shared<Drawable>(info, material, indexed);
  drawable->create(vtxdata);
  subqueue->addDrawable(drawable);
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
