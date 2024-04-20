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
#include <utility>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class Material : public core::foundation::Uniqueable<std::string> {
public:
  Material(const std::string &name, std::shared_ptr<rms::ImageResourceManager> imageResMngr,
      std::shared_ptr<rms::GLSLResourceManager> glslResMngr);

  ~Material() = default;

  auto addImage(const std::string &resname, const std::string &alias) -> bool;

  auto addImage(const gapi::TextureCreateInfo &createInfo, const std::string &alias) -> Image::Ptr;

  auto addEffect(const std::array<std::string, 2> &names) -> bool;

  void bind(const std::shared_ptr<math::MatrixStack> &mtxs);

  void unbind();

  auto getEffect() -> EffectPtr_t { return effect_; }

  auto getImages() -> std::vector<std::pair<std::string, Image::Ptr>> { return images_; }

  gapi::ShaderCreateInfoSet shaderCreateInfoSet_;

public:
  void addShader_(const std::string &name, gapi::ShaderCreateInfo &info, gapi::ShaderType type);

  std::shared_ptr<rms::ImageResourceManager> imageResMngr_;
  std::shared_ptr<rms::GLSLResourceManager> glslResMngr_;
  EffectPtr_t effect_;
  std::vector<std::pair<std::string, Image::Ptr>> images_;
  MaterialDescriptor desc_;
  Image::Ptr image_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_MATERIAL_HPP
