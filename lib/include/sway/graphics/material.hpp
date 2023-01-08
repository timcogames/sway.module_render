#ifndef SWAY_GRAPHICS_MATERIAL_HPP
#define SWAY_GRAPHICS_MATERIAL_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Material {
public:
  Material();

  ~Material() = default;

  auto loadImage(const std::string &resourceName) -> bool;

  auto loadEffect(const std::string &resourceName) -> bool;

  void bind();

  void unbind();

  std::shared_ptr<render::Effect> getEffect() { return effect_; }

private:
  std::shared_ptr<render::Effect> effect_;

  math::col4f_t ambient_;
  math::col4f_t diffuse_;
  math::col4f_t specular_;
  math::col4f_t emissive_;
  f32_t shininess_;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_MATERIAL_HPP
