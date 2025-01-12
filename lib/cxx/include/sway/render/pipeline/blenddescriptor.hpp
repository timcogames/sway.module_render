#ifndef SWAY_RENDER_PIPELINE_BLENDDESCRIPTOR_HPP
#define SWAY_RENDER_PIPELINE_BLENDDESCRIPTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

namespace sway::render {
NS_BEGIN(pipeline)

struct BlendDescriptor {
  bool enabled;
  gapi::BlendFn::Enum src;
  gapi::BlendFn::Enum dst;
  bool mask;
};

NS_END()  // namespace pipeline
}  // namespace sway::render

#endif  // SWAY_RENDER_PIPELINE_BLENDDESCRIPTOR_HPP
