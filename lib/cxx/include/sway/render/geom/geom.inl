#include <sway/core.hpp>
#include <sway/render/geom/geom.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

template <class TObject>
void Geom::call(std::function<void(TObject)> callback) {
  for (auto buf : buffers_) {
    if (buf.has_value()) {
      callback(buf.value());
    }
  }
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
