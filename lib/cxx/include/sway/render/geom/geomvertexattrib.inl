#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/geom/geomvertexattrib.hpp>
#include <sway/render/geom/geomvertexdata.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <typename TAttribFormat>
GeomVertexAttrib<TAttribFormat>::GeomVertexAttrib(
    GeomVertexDataBase *owner, gapi::VertexSemantic semantic, bool normalized)
    : owner_(owner)
    , descriptor_(gapi::VertexAttribDescriptor::merge<TAttribFormat>(semantic, normalized, true))
    , data_(new VertexAttribType_t[owner_->getVertexCount() * sizeof(VertexAttribType_t)])
    , enabled_(false) {}

NAMESPACE_END(render)
NAMESPACE_END(sway)
