#ifndef SWAY_GRAPHICS_MATERIAL_HPP
#define SWAY_GRAPHICS_MATERIAL_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render.hpp>
#include <sway/rms.hpp>

#include <memory>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

class Material {
public:
  Material(std::shared_ptr<rms::ResourceManagerSystem> resmgr);

  ~Material() = default;

  auto loadImage(const std::string &name) -> bool;

  auto loadEffect(const std::string &name) -> bool;

  void bind();

  void unbind();

  std::shared_ptr<render::Effect> getEffect() { return effect_; }

private:
  std::shared_ptr<rms::ResourceManagerSystem> resmgr_;
  std::shared_ptr<render::Effect> effect_;
  std::vector<std::shared_ptr<render::Image>> images_;

  math::col4f_t ambient_;
  math::col4f_t diffuse_;
  math::col4f_t specular_;
  math::col4f_t emissive_;
  f32_t shininess_;
};

NAMESPACE_END(graphics)
NAMESPACE_END(sway)

#endif  // SWAY_GRAPHICS_MATERIAL_HPP
