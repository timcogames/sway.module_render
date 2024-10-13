#ifndef SWAY_RENDER_GEOMPASS_HPP
#define SWAY_RENDER_GEOMPASS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/temp/pipeline/stage/pass/pass.hpp>
#include <sway/render/temp/pipeline/stage/pass/passtypes.hpp>

#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class GeomPass : public Pass {
public:
  GeomPass(const std::string &name)
      : Pass(core::detail::toBase(PassType::Enum::GEOM), name) {}

  DTOR_VIRTUAL_DEFAULT(GeomPass);

  MTHD_OVERRIDE(void setup()) {}

  MTHD_OVERRIDE(void dispose()) {}

  MTHD_OVERRIDE(void apply(gapi::FrameBuffer::Ptr_t framebuf)) {}

  MTHD_OVERRIDE(void execute()) {}
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_GEOMPASS_HPP
