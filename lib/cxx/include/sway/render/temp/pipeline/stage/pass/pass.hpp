#ifndef SWAY_RENDER_PASS_HPP
#define SWAY_RENDER_PASS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/temp/pipeline/stage/pass/passtypes.hpp>

#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Pass {
  DECLARE_PTR_ALIASES(Pass)
  DECLARE_PTR_VECTOR(Pass, SharedPtr)

public:
  Pass(u32_t type, const std::string &name)
      : type_(type)
      , name_(name) {}

  DTOR_VIRTUAL_DEFAULT(Pass);

  PURE_VIRTUAL(void setup());

  PURE_VIRTUAL(void dispose());

  PURE_VIRTUAL(void apply(gapi::FrameBuffer::Ptr_t framebuf));

  PURE_VIRTUAL(void execute());

  auto type() const -> u32_t { return type_; }

  auto name() const -> const std::string & { return name_; }

private:
  u32_t type_;
  std::string name_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PASS_HPP
