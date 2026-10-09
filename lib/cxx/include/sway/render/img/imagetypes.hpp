#ifndef SWAY_RENDER_IMAGETYPES_HPP
#define SWAY_RENDER_IMAGETYPES_HPP

#include <sway/render/_typedefs.hpp>

namespace sway::render {

// clang-format off
#define IMAGE_TYPE_LIST(ITEM) \
  ITEM(IDX_ALBEDO, 0) \
  ITEM(IDX_NORMAL, 1) \
  ITEM(IDX_SURFACE, 2) \
  ITEM(IDX_REFLECTIVITY, 3) \
  ITEM(IDX_OCCLUSION, 4) \
  ITEM(IDX_EMISSIVE, 5)
// clang-format on

DECLARE_ENUM_IDX(ImageType, IMAGE_TYPE_LIST)

}  // namespace sway::render

#endif  // SWAY_RENDER_IMAGETYPES_HPP
