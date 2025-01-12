#include <sway/core.hpp>
#include <sway/render/geom/geom.hpp>

namespace sway::render {

template <class OBJ>
void Geom::call(std::function<void(OBJ)> callback) {
  for (auto buf : buffers_) {
    if (buf.has_value()) {
      callback(buf.value());
    }
  }
}

}  // namespace sway::render
