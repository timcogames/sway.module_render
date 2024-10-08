#include <sway/core.hpp>
#include <sway/render/geom/geom.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

template <class OBJ>
void Geom::call(std::function<void(OBJ)> callback) {
  for (auto buf : buffers_) {
    if (buf.has_value()) {
      callback(buf.value());
    }
  }
}

NS_END()  // namespace render
NS_END()  // namespace sway
