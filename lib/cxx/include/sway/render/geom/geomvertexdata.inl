#include <sway/core.hpp>
#include <sway/render/geom/geomvertexdata.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

template <typename TVertexDataType>
template <typename TAttribFormat>
auto GeomVertexData<TVertexDataType>::createAttrib(gapi::VertexSemantic semantic) -> GeomVertexAttribBase::SharedPtr_t {
  auto attrib = std::make_shared<GeomVertexAttrib<TAttribFormat>>(this, semantic, false);
  attribs_[semantic] = attrib;
  return attrib;
}

NS_END()  // namespace render
NS_END()  // namespace sway
