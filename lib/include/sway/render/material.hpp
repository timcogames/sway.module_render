#ifndef SWAY_RENDER_MATERIAL_HPP
#define SWAY_RENDER_MATERIAL_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect.hpp>
#include <sway/render/image.hpp>
#include <sway/render/materialdescriptor.hpp>
#include <sway/rms.hpp>

#include <memory>
#include <optional>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class Material : public core::foundation::Uniqueable<std::string> {
public:
  Material(const std::string &name, std::shared_ptr<rms::ImageResourceManager> imageResMngr,
      std::shared_ptr<rms::GLSLResourceManager> glslResMngr);

  ~Material() = default;

  auto addImage(const std::string &name) -> bool;

  auto addEffect(const std::array<std::string, 2> &names) -> bool;

  void bind();

  void unbind();

  auto getEffect() -> std::shared_ptr<Effect> { return effect_; }

  auto getImages() -> std::vector<std::shared_ptr<Image>> { return images_; }

  [[nodiscard]] auto getImageSize() const -> math::size2f_t {
    return math::size2f_t((f32_t)imgDesc_.size.getW(), (f32_t)imgDesc_.size.getH());
  }

  gapi::ShaderCreateInfoSet shaderCreateInfoSet_;

public:
  void addShader_(const std::string &name, gapi::ShaderCreateInfo &info, gapi::ShaderType type);

  std::shared_ptr<rms::ImageResourceManager> imageResMngr_;
  std::shared_ptr<rms::GLSLResourceManager> glslResMngr_;
  std::shared_ptr<Effect> effect_;
  std::vector<std::shared_ptr<Image>> images_;
  MaterialDescriptor desc_;
  loader::ImageDescriptor imgDesc_;
  std::shared_ptr<Image> image_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_MATERIAL_HPP
