#ifndef SWAY_RENDER_MTRL_MATERIAL_HPP
#define SWAY_RENDER_MTRL_MATERIAL_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/effect/_typedefs.hpp>
#include <sway/render/effect/effect.hpp>
#include <sway/render/global.hpp>
#include <sway/render/img/_typedefs.hpp>
#include <sway/render/img/image.hpp>
#include <sway/render/mtrl/_typedefs.hpp>
#include <sway/render/mtrl/materialdescriptor.hpp>
#include <sway/rms.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Material : public core::Uniqueable<std::string> {
public:
#pragma region "Ctors/Dtor"

  Material(global::GapiPluginFunctionSet *plug, const std::string &name);

  Material(const std::string &name, std::shared_ptr<rms::ImageResourceManager> imageResMngr,
      std::shared_ptr<rms::GLSLResourceManager> glslResMngr);

  DTOR_DEFAULT(Material);

#pragma endregion

#pragma region "Adding/Updating/Removing"

  void addImage(const std::string &alias, ImageTypedefs::SharedPtr_t img);

  auto addImage(const std::string &resname, const std::string &alias) -> bool;

  auto addImage(const gapi::TextureCreateInfo &createInfo, const std::string &alias) -> ImageTypedefs::SharedPtr_t;

  void addEffectSource(const ShaderTypedefs::SourcePair_t &sources);

  void addEffect(const ShaderTypedefs::NamePair_t &names);

#pragma endregion

#pragma region "Binding/Unbinding"

  void bind(const std::shared_ptr<math::MatrixStack> &mtxs);

  void unbind();

#pragma endregion

#pragma region "Getters/Setters"

  void setImageManager(std::shared_ptr<rms::ImageResourceManager> mngr) { imageResMngr_ = mngr; }

  void setShaderManager(std::shared_ptr<rms::GLSLResourceManager> mngr) { glslResMngr_ = mngr; }

  auto getEffect() -> EffectTypedefs::Ptr_t { return effect_; }

  auto getImages() -> ImageTypedefs::Container_t { return images_; }

  auto getImage(u32_t idx) -> ImageTypedefs::SharedPtr_t {
    return (idx < images_.size()) ? images_[idx].second : nullptr;
  }

  void setSubsys(typedefs::RenderSubsystemPtr_t subsys);

#pragma endregion

public:
  void addShader_(const std::string &name, gapi::ShaderCreateInfo &info, gapi::ShaderType::Enum type);

  global::GapiPluginFunctionSet *pluginFuncSet_;
  std::shared_ptr<rms::ImageResourceManager> imageResMngr_;
  std::shared_ptr<rms::GLSLResourceManager> glslResMngr_;
  EffectTypedefs::Ptr_t effect_;
  ImageTypedefs::Container_t images_;
  MaterialDescriptor desc_;

  typedefs::RenderSubsystemPtr_t subsys_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_MTRL_MATERIAL_HPP
