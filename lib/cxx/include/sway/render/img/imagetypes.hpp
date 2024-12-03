#ifndef SWAY_RENDER_IMAGETYPES_HPP
#define SWAY_RENDER_IMAGETYPES_HPP

#include <sway/render/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

// clang-format off
DECLARE_ENUM_IDX(ImageType, 
  IDX_ALBEDO, 
  IDX_NORMAL, 
  IDX_SURFACE, 
  IDX_REFLECTIVITY, 
  IDX_OCCLUSION, 
  IDX_EMISSIVE)
// clang-format on

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_IMAGETYPES_HPP
