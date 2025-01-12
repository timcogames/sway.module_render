#ifndef SWAY_RENDER_IMAGEDATAPACK_HPP
#define SWAY_RENDER_IMAGEDATAPACK_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/_typedefs.hpp>
#include <sway/render/img/_typedefs.hpp>
#include <sway/render/img/pixel.hpp>

namespace sway::render {

struct ImageDataPack {
  PixelTypedefs::Ptr_t bytes;
  math::rect4i_t bounds;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_IMAGEDATAPACK_HPP
