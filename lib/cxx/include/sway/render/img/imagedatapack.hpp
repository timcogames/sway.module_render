#ifndef SWAY_RENDER_IMAGEDATAPACK_HPP
#define SWAY_RENDER_IMAGEDATAPACK_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/img/_typedefs.hpp>
#include <sway/render/img/pixel.hpp>
#include <sway/render/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

struct ImageDataPack {
  PixelTypedefs::Ptr_t bytes;
  math::rect4i_t bounds;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_IMAGEDATAPACK_HPP
