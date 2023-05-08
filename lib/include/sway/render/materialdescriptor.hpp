#ifndef SWAY_RENDER_MATERIALDESCRIPTOR_HPP
#define SWAY_RENDER_MATERIALDESCRIPTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>

#include <memory>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

struct MaterialDescriptor {
  math::col4f_t ambient;
  math::col4f_t diffuse;
  math::col4f_t specular;
  math::col4f_t emissive;
  f32_t shininess;

  MaterialDescriptor() {
    ambient = diffuse = specular = emissive = {0.0F, 0.0F, 0.0F, 1.0F};
    shininess = 0.0F;
  }
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_MATERIALDESCRIPTOR_HPP
