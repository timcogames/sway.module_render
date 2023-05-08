#ifndef SWAY_RENDER_POSTPROCESSING_HPP
#define SWAY_RENDER_POSTPROCESSING_HPP

#include <sway/gapi.hpp>
#include <sway/namespacemacros.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class PostProcessing {
public:
  PostProcessing() = default;

  ~PostProcessing() = default;

  void postProcess(std::shared_ptr<gapi::Texture> finalColor);

private:
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_POSTPROCESSING_HPP
