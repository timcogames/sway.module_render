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

auto Material::addImage(const std::string &name) -> bool {
  auto resource = imageResMngr_->findLoadedResource(name);

#if EMSCRIPTEN_PLATFORM

  while (!resource->loadingDone_.load(std::memory_order_relaxed)) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

#endif

  imgDesc_ = resource->getDescriptor();

  auto image = std::make_shared<Image>();
  image->create(imgDesc_.buf.data, imgDesc_.size.getW(), imgDesc_.size.getH());
  image->getTexture()->bind();
  image->getTextureSampler()->setWrapMode(
      gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT);
  image->getTextureSampler()->setFilterMode(gapi::TextureFilter::NEAREST, gapi::TextureFilter::NEAREST);
  image->getTexture()->unbind();

  images_.push_back(image);

  return true;
}

void Material::addShader_(const std::string &name, gapi::ShaderCreateInfo &info, gapi::ShaderType type) {
  auto resource = glslResMngr_->findLoadedResource(name);

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

void Material::bind() {
  // effect_->getShaderProgram()->setUniformCol4f("mat_ambient", desc.ambient);
  // effect_->getShaderProgram()->setUniformCol4f("mat_diffuse", desc.diffuse);
  // effect_->getShaderProgram()->setUniformCol4f("mat_specular", desc.specular);
  // effect_->getShaderProgram()->setUniformCol4f("mat_emissive", desc.emissive);
  //  // effect_->getShaderProgram()->setUniform1f("mat_shininess", desc.shininess);

  if (!images_.empty()) {
    effect_->getShaderProgram()->setUniform1i("diffuse_sampler", images_[0]->getTexture()->getUid().value());
  }

  // effect_->bind();

  for (auto image : images_) {
    image->getTexture()->setActive(images_[0]->getTexture()->getUid().value());
    image->bind();
  }
}

void Material::unbind() {
  for (auto image : images_) {
    image->unbind();
  }

  // effect_->unbind();
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
