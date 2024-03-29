#include <sway/gapi/texturefilters.hpp>
#include <sway/gapi/texturesampler.hpp>
#include <sway/gapi/texturewraps.hpp>
#include <sway/render/material.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Material::Material(const std::string &name, std::shared_ptr<rms::ImageResourceManager> mngr)
    : core::foundation::Uniqueable<std::string>(name)
    , resourceMngr_(mngr)
    , effect_(nullptr) {}

auto Material::addImage(const std::string &name) -> bool {
  auto resource = resourceMngr_->findLoadedResource(name);

  imgDesc_ = resource->getDescriptor();
  // std::cout << name.c_str() << ": " << imgDesc_.size.getW() << "x" << imgDesc_.size.getH() << std::endl;
  auto image = std::make_shared<Image>(imgDesc_.buf.data, imgDesc_.size.getW(), imgDesc_.size.getH());

  image->getTexture()->bind();
  image->getTextureSampler()->setWrapMode(
      gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT, gapi::TextureWrap::REPEAT);
  image->getTextureSampler()->setFilterMode(gapi::TextureFilter::NEAREST, gapi::TextureFilter::NEAREST);
  image->getTexture()->unbind();

  images_.push_back(image);

  return true;
}

auto Material::loadEffect(const std::pair<std::string, std::string> &filepath) -> bool {
  gapi::ShaderCreateInfoSet shaderCreateInfoSet;

  auto vert = this->loadShaderFromFile(filepath.first);
  if (!vert.has_value()) {
    return false;
  }

  shaderCreateInfoSet.vs.type = gapi::ShaderType::VERT;
  shaderCreateInfoSet.vs.code = vert.value();

  auto frag = this->loadShaderFromFile(filepath.second);
  if (!frag.has_value()) {
    return false;
  }

  shaderCreateInfoSet.fs.type = gapi::ShaderType::FRAG;
  shaderCreateInfoSet.fs.code = frag.value();

  effect_ = std::make_shared<Effect>(shaderCreateInfoSet);
  return true;
}

auto Material::loadShaderFromFile(const std::string &filename) -> std::optional<std::string> {
  std::ifstream stream(filename, std::ios::binary);
  if (!stream.is_open()) {
    return std::nullopt;
  }

  std::string source((std::istreambuf_iterator<s8_t>(stream)), std::istreambuf_iterator<s8_t>());
  stream.close();

  if (source.length() == 0) {
    return std::nullopt;
  }

  return source;
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
