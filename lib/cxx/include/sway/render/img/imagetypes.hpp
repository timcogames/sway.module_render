#ifndef SWAY_RENDER_IMAGETYPES_HPP
#define SWAY_RENDER_IMAGETYPES_HPP

#include <sway/render/_typedefs.hpp>

namespace sway::render {

// clang-format off
DECLARE_ENUM_IDX(ImageType, 
  IDX_ALBEDO, 
  IDX_NORMAL, 
  IDX_SURFACE, 
  IDX_REFLECTIVITY, 
  IDX_OCCLUSION, 
  IDX_EMISSIVE)
// clang-format on

}  // namespace sway::render

#endif  // SWAY_RENDER_IMAGETYPES_HPP
