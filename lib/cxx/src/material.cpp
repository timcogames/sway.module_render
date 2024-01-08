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
    , imageResMngr_(imageResMngr)
    , glslResMngr_(glslResMngr)
    , effect_(nullptr) {}

auto Material::addImage(const std::string &resname, const std::string &alias) -> bool {
  auto resource = imageResMngr_->findLoadedResource(resname);
  if (!resource) {
    printf("The file %s was not found\n", resname.c_str());
  }

#if EMSCRIPTEN_PLATFORM

  resource->wait(std::chrono::milliseconds(10));

#endif

  imgDesc_ = resource->getDescriptor();

  auto image = std::make_shared<Image>();
  image->create(imgDesc_.buf.data, imgDesc_.size.getW(), imgDesc_.size.getH());
  image->getTexture()->bind();
  image->getTextureSampler()->setWrapMode(
      gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT);
  image->getTextureSampler()->setFilterMode(gapi::TextureFilter::NEAREST, gapi::TextureFilter::NEAREST);
  image->getTexture()->unbind();

  images_.push_back({alias, image});

  return true;
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
}

auto Material::addEffect(const std::array<std::string, 2> &names) -> bool {
  addShader_(std::get<0>(names), shaderCreateInfoSet_.vs, gapi::ShaderType::VERT);
  addShader_(std::get<1>(names), shaderCreateInfoSet_.fs, gapi::ShaderType::FRAG);

  effect_ = std::make_shared<Effect>(shaderCreateInfoSet_);
  return true;
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
    effect_->getShaderProgram()->setUniform1i(image.first, image.second->getTexture()->getUid().value());
  }

  effect_->getShaderProgram()->setUniformMat4f("mat_view", viewMtx);
  effect_->getShaderProgram()->setUniformMat4f("mat_proj", projMtx);
  effect_->getShaderProgram()->setUniformMat4f("mat_view_proj", viewProjMtx);
  effect_->getShaderProgram()->setUniformMat4f("mat_model", tfrmMtx);
  effect_->bind();

  for (auto image : images_) {
    // state_->apply();
    image.second->getTexture()->setActive(image.second->getTexture()->getUid().value());
    image.second->bind();
  }
}

void Material::unbind() {
  for (auto image : images_) {
    image.second->unbind();
  }

  effect_->unbind();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
