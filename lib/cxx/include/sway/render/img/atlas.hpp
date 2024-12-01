#ifndef SWAY_RENDER_ATLAS_HPP
#define SWAY_RENDER_ATLAS_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/img/_typedefs.hpp>
#include <sway/render/img/imagedatapack.hpp>
#include <sway/render/img/pixel.hpp>
#include <sway/render/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class AtlasBuilder {
public:
#pragma region "Ctors/Dtor"

  AtlasBuilder() = default;

  DTOR_DEFAULT(AtlasBuilder);

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

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_ATLAS_HPP
