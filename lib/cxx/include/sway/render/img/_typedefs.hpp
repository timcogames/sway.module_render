#ifndef SWAY_RENDER_IMG_TYPEDEFS_HPP
#define SWAY_RENDER_IMG_TYPEDEFS_HPP

#include <sway/render/img/pixel.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

namespace PixelTypedefs {
using Ptr_t = Pixel_t *;
}  // namespace PixelTypedefs

class Image;
namespace ImageTypedefs {
using Ptr_t = Image *;
using SharedPtr_t = std::shared_ptr<Image>;
using Container_t = std::vector<std::pair<std::string, SharedPtr_t>>;
}  // namespace ImageTypedefs

struct ImageDataPack;
namespace ImageDataPackTypedefs {
using Container_t = std::vector<ImageDataPack>;
}  // namespace ImageDataPackTypedefs

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_IMG_TYPEDEFS_HPP
