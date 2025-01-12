#ifndef SWAY_RENDER_ATLAS_HPP
#define SWAY_RENDER_ATLAS_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/_typedefs.hpp>
#include <sway/render/img/_typedefs.hpp>
#include <sway/render/img/imagedatapack.hpp>
#include <sway/render/img/pixel.hpp>

namespace sway::render {

class AtlasBuilder {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  AtlasBuilder() = default;

  DTOR_DEFAULT(AtlasBuilder);

  /** @} */
#pragma endregion

  void addImage(const PixelTypedefs::Ptr_t src, math::size2i_t dims) {
    ImageDataPack pack;
    pack.bytes = new Pixel_t[dims.area()];
    memcpy(pack.bytes, src, dims.area() * 4);
    pack.bounds.set(0, 0, dims);

    packages_.push_back(pack);
  }

private:
  ImageDataPackTypedefs::Container_t packages_;
};

}  // namespace sway::render

#endif  // SWAY_RENDER_ATLAS_HPP
