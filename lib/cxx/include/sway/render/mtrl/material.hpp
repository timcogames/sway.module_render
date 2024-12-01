#ifndef SWAY_RENDER_MTRL_MATERIAL_HPP
#define SWAY_RENDER_MTRL_MATERIAL_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/effect/effect.hpp>
#include <sway/render/global.hpp>
#include <sway/render/img/_typedefs.hpp>
#include <sway/render/img/image.hpp>
#include <sway/render/mtrl/materialdescriptor.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/rms.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Material : public core::foundation::Uniqueable<std::string> {
public:
#pragma region "Ctors/Dtor"

  Material(const std::string &name, std::shared_ptr<rms::ImageResourceManager> imageResMngr,
      std::shared_ptr<rms::GLSLResourceManager> glslResMngr);

  DTOR_DEFAULT(Material);

#pragma endregion

#pragma region "Adding/Updating/Removing"

  void addImage(const std::string &alias, ImageTypedefs::SharedPtr_t img);

  auto addImage(const std::string &resname, const std::string &alias) -> bool;

  auto addImage(const gapi::TextureCreateInfo &createInfo, const std::string &alias) -> ImageTypedefs::SharedPtr_t;

  void addEffect(std::unordered_map<gapi::ShaderType::Enum, std::string> sources);

  void addEffect(const std::array<std::string, 2> &names);

#pragma endregion

#pragma region "Binding/Unbinding"

  void bind(const std::shared_ptr<math::MatrixStack> &mtxs);

  void unbind();

#pragma endregion

#pragma region "Getters/Setters"

  auto getEffect() -> EffectTypedefs::Ptr_t { return effect_; }

  auto getImages() -> ImageTypedefs::Container_t { return images_; }

  auto getImage(u32_t idx) -> ImageTypedefs::SharedPtr_t { return images_[idx].second; }

  void setSubsys(RenderSubsystemPtr_t subsys);

#pragma endregion

public:
  void addShader_(const std::string &name, gapi::ShaderCreateInfo &info, gapi::ShaderType::Enum type);

  global::GapiPluginFunctionSet *pluginFuncSet_;
  std::shared_ptr<rms::ImageResourceManager> imageResMngr_;
  std::shared_ptr<rms::GLSLResourceManager> glslResMngr_;
  EffectTypedefs::Ptr_t effect_;
  ImageTypedefs::Container_t images_;
  MaterialDescriptor desc_;

  RenderSubsystemPtr_t subsys_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_MTRL_MATERIAL_HPP
