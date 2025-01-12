#ifndef SWAY_RENDER_EFFECTRESOURCE_HPP
#define SWAY_RENDER_EFFECTRESOURCE_HPP

#include <sway/render/_stdafx.hpp>
#include <sway/render/effect/_typedefs.hpp>

namespace sway::render {

struct EffectResource final {
  std::string name;
  std::size_t hash;
  std::atomic_bool ready{false};
};

}  // namespace sway::render

#endif  // SWAY_RENDER_EFFECTRESOURCE_HPP
