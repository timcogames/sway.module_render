#ifndef SWAY_RENDER_PIPELINE_BLENDDESCRIPTOR_HPP
#define SWAY_RENDER_PIPELINE_BLENDDESCRIPTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(pipeline)

struct BlendDescriptor {
  bool enabled;
  gapi::BlendFn::Enum src;
  gapi::BlendFn::Enum dst;
  bool mask;
};

NS_END()  // namespace pipeline
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PIPELINE_BLENDDESCRIPTOR_HPP
