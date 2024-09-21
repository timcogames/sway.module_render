#include <sway/gapi/texturefilters.hpp>
#include <sway/gapi/texturesampler.hpp>
#include <sway/gapi/texturewraps.hpp>
#include <sway/render/material.hpp>

#include <thread>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Material::Material(const std::string &name, std::shared_ptr<rms::ImageResourceManager> imageResMngr,
    std::shared_ptr<rms::GLSLResourceManager> glslResMngr)
    : core::foundation::Uniqueable<std::string>(name)
    , pluginFuncSet_(global::getGapiPluginFunctionSet())
    , imageResMngr_(imageResMngr)
    , glslResMngr_(glslResMngr)
    , effect_(nullptr) {}

void Material::addImage(const std::string &alias, Image::SharedPtr_t img) { images_.push_back({alias, img}); }

auto Material::addImage(const std::string &resname, const std::string &alias) -> bool {
  auto resource = imageResMngr_->findLoadedResource(resname);
  if (!resource) {
    printf("The file %s was not found\n", resname.c_str());
  }

#if EMSCRIPTEN_PLATFORM

  resource->wait(std::chrono::milliseconds(10));

#endif

  auto image = std::make_shared<Image>();
  image->create(resource->getDescriptor());
  image->getTextureSampler()->setWrapMode(
      gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT);
  image->getTextureSampler()->setFilterMode(gapi::TextureFilter::NEAREST, gapi::TextureFilter::NEAREST);

  addImage(alias, image);
  return true;
}

auto Material::addImage(const gapi::TextureCreateInfo &createInfo, const std::string &alias) -> Image::SharedPtr_t {
  auto image = std::make_shared<Image>();

#ifndef EMSCRIPTEN_PLATFORM
  // image->getTexture()->setUnpackAlignement(1);
#endif

  image->create(createInfo);
  image->getTextureSampler()->setWrapMode(
      gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT);
  image->getTextureSampler()->setFilterMode(gapi::TextureFilter::NEAREST, gapi::TextureFilter::NEAREST);

  addImage(alias, image);
  return image;
}

void Material::addShader_(const std::string &name, gapi::ShaderCreateInfo &info, gapi::ShaderType type) {
  auto resource = glslResMngr_->findLoadedResource(name);
  if (!resource) {
    printf("The file %s was not found\n", name.c_str());
  }

#if EMSCRIPTEN_PLATFORM

  while (!resource->loadingDone_.load(std::memory_order_relaxed)) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

#endif

  info.type = type;
  info.code = resource->content_;
  info.preprocessor = pluginFuncSet_->createShaderPreprocessor(300, "es");
}

void Material::addEffect(std::unordered_map<gapi::ShaderType, std::string> sources) {
  gapi::ShaderCreateInfoSet createInfoSet;
  createInfoSet.vs.type = gapi::ShaderType::VERT;
  createInfoSet.vs.code = sources[gapi::ShaderType::VERT];
  createInfoSet.vs.preprocessor = pluginFuncSet_->createShaderPreprocessor(300, "es");

  createInfoSet.fs.type = gapi::ShaderType::FRAG;
  createInfoSet.fs.code = sources[gapi::ShaderType::FRAG];
  createInfoSet.fs.preprocessor = pluginFuncSet_->createShaderPreprocessor(300, "es");

  effect_ = Effect::create(createInfoSet);
}

void Material::addEffect(const std::array<std::string, 2> &names) {
  gapi::ShaderCreateInfoSet createInfoSet;
  addShader_(std::get<0>(names), createInfoSet.vs, gapi::ShaderType::VERT);
  addShader_(std::get<1>(names), createInfoSet.fs, gapi::ShaderType::FRAG);

  effect_ = Effect::create(createInfoSet);
}

void Material::bind(const std::shared_ptr<math::MatrixStack> &mtxs) {
  auto viewMtx = mtxs->top<math::MatrixType::VIEW>();
  auto projMtx = mtxs->top<math::MatrixType::PROJ>();
  auto tfrmMtx = mtxs->top<math::MatrixType::TFRM>();

  auto viewProjMtx = viewMtx * projMtx;

  // effect_->getShaderProgram()->setUniformCol4f("mat_ambient", desc.ambient);
  // effect_->getShaderProgram()->setUniformCol4f("mat_diffuse", desc.diffuse);
  // effect_->getShaderProgram()->setUniformCol4f("mat_specular", desc.specular);
  // effect_->getShaderProgram()->setUniformCol4f("mat_emissive", desc.emissive);
  // effect_->getShaderProgram()->setUniform1f("mat_shininess", desc.shininess);

  for (auto image : images_) {
    auto texUid = image.second->getTexture()->getUid();
    if (!texUid.has_value()) {
      return;
    }

    image.second->getTexture()->setActive(texUid.value());
    image.second->bind();

    effect_->getShaderProgram()->setUniform1i(image.first, texUid.value());
  }

  effect_->getShaderProgram()->setUniformMat4f("mat_view", viewMtx);
  effect_->getShaderProgram()->setUniformMat4f("mat_proj", projMtx);
  effect_->getShaderProgram()->setUniformMat4f("mat_view_proj", viewProjMtx);
  effect_->getShaderProgram()->setUniformMat4f("mat_model", tfrmMtx);
  effect_->bind();
}

void Material::unbind() {
  for (auto image : images_) {
    image.second->unbind();
    image.second->getTexture()->setActive(0);
  }

  effect_->unbind();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
