#ifndef SWAY_RENDER_ATLAS_HPP
#define SWAY_RENDER_ATLAS_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

#include <unordered_map>
#include <vector>

NS_BEGIN_SWAY()
NS_BEGIN(render)

using Pixel = u32_t;
// struct Pixel {
//   u8_t r;
//   u8_t g;
//   u8_t b;
//   u8_t a;
// };

struct ImageDataPack {
  Pixel *bytes;
  math::rect4i_t bounds;
};

struct ImageData {
  Pixel *bytes;
  math::rect4i_t bounds;
};

class AtlasBuilder {
public:
  AtlasBuilder() {}

  ~AtlasBuilder() = default;

  void addImage(const Pixel *src, math::size2i_t size) {
    ImageDataPack pack;
    pack.bytes = new Pixel[size.area()];
    memcpy(pack.bytes, src, size.area() * 4);
    pack.bounds.set(0, 0, size);

    packages_.push_back(pack);
  }

private:
  std::vector<ImageDataPack> packages_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_ATLAS_HPP
