#include "webapp.hpp"

#include <sway/core.hpp>

#include <emscripten/html5.h>

using namespace sway;

auto main() -> int {
  if (!emscripten_supports_offscreencanvas()) {
    printf("Browser does not support OffscreenCanvas");
    return -1;
  }

  createWorker();
  return 0;
}
