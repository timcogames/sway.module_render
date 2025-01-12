#include <sway/core.hpp>
#include <sway/render/geom/geomvertexdata.hpp>

namespace sway::render {

template <typename TVertexDataType>
template <typename TAttribFormat>
auto GeomVertexData<TVertexDataType>::createAttrib(gapi::VertexSemantic semantic) -> GeomVertexAttribBaseSharedPtr_t {
  auto attrib = std::make_shared<GeomVertexAttrib<TAttribFormat>>(this, semantic, false);
  attribs_[semantic] = attrib;
  return attrib;
}

}  // namespace sway::render
