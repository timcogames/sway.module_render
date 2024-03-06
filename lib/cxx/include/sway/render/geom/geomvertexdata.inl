#include <sway/core.hpp>
#include <sway/render/geom/geomvertexdata.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TVertexDataType>
template <typename TAttribFormat>
auto GeomVertexData<TVertexDataType>::createAttrib(gapi::VertexSemantic semantic)
    -> std::shared_ptr<GeomVertexAttribBase> {
  auto attrib = std::make_shared<GeomVertexAttrib<TAttribFormat>>(this, semantic, false);
  attribs_[semantic] = attrib;
  return attrib;
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
