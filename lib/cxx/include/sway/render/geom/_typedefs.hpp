#ifndef SWAY_RENDER_GEOM_TYPEDEFS_HPP
#define SWAY_RENDER_GEOM_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Geom;
namespace GeomTypedefs {
using Ptr_t = Geom *;
using Container_t = std::vector<Ptr_t>;
}  // namespace GeomTypedefs

class GeomBuilder;
namespace GeomBuilderTypedefs {
using SharedPtr_t = std::shared_ptr<GeomBuilder>;
using Container_t = std::vector<SharedPtr_t>;
}  // namespace GeomBuilderTypedefs

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_GEOM_TYPEDEFS_HPP
