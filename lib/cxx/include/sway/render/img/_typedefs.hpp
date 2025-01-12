#ifndef SWAY_RENDER_IMG_TYPEDEFS_HPP
#define SWAY_RENDER_IMG_TYPEDEFS_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/img/imagetypes.hpp>
#include <sway/render/img/pixel.hpp>

namespace sway::render {

namespace PixelTypedefs {
using Ptr_t = Pixel_t *;
}  // namespace PixelTypedefs

class Image;
namespace ImageTypedefs {
using Ptr_t = Image *;
using SharedPtr_t = std::shared_ptr<Image>;
using Container_t = std::vector<std::pair<std::string, SharedPtr_t>>;
// using Container_t = std::array<std::optional<SharedPtr_t>, ImageTypeLatest>;
}  // namespace ImageTypedefs

struct ImageDataPack;
namespace ImageDataPackTypedefs {
using Container_t = std::vector<ImageDataPack>;
}  // namespace ImageDataPackTypedefs

}  // namespace sway::render

#endif  // SWAY_RENDER_IMG_TYPEDEFS_HPP
