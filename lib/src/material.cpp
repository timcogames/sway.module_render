#include <sway/gapi/texturefilters.hpp>
#include <sway/gapi/texturesampler.hpp>
#include <sway/gapi/texturewraps.hpp>
#include <sway/render/material.hpp>

#include <thread>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Material::Material(const std::string &name, std::shared_ptr<rms::ImageResourceManager> mngr)
    : core::foundation::Uniqueable<std::string>(name)
    , resourceMngr_(mngr)
    , effect_(nullptr) {}

auto Material::addImage(const std::string &name) -> bool {
  auto resource = resourceMngr_->findLoadedResource(name);

  while (!resource->loadingDone_.load(std::memory_order_relaxed)) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

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

auto Material::loadEffect(const std::pair<std::string, std::string> &filepath) -> bool {
  // gapi::ShaderCreateInfoSet shaderCreateInfoSet;

  // auto vert = this->loadShaderFromFile(filepath.first);
  // if (!vert.has_value()) {
  //   printf("failed: %s\n", filepath.first.c_str());
  //   return false;
  // }

  // shaderCreateInfoSet.vs.type = gapi::ShaderType::VERT;
  // shaderCreateInfoSet.vs.code = vert.value();

  // auto frag = this->loadShaderFromFile(filepath.second);
  // if (!frag.has_value()) {
  //   return false;
  // }

  // shaderCreateInfoSet.fs.type = gapi::ShaderType::FRAG;
  // shaderCreateInfoSet.fs.code = frag.value();

  loadVShaderFromFile(filepath.first);
  loadFShaderFromFile(filepath.second);

  effect_ = std::make_shared<Effect>(shaderCreateInfoSet_);
  return true;
}

void onShaderErrorRequest(void *arg) {}

auto dataToChar(void *data, int size) -> char * {
  char *tmp = new char[size + 1];
  memcpy(tmp, data, size * sizeof(char));
  tmp[size] = '\0';

  return tmp;
}

auto Material::onLoadVSFromFile(void *buffer, int size) -> std::string { return std::string(dataToChar(buffer, size)); }

void Material::loadVShaderFromFile(const std::string &filename) {
  // emscripten_idb_async_exists
  // emscripten_async_wget_data(
  //     filename.c_str(), this,
  //     [](void *arg, void *buffer, int size) -> void {
  //       auto *materialPtr = (Material *)arg;
  //       auto content = materialPtr->onLoadVSFromFile(buffer, size);

  //       materialPtr->shaderCreateInfoSet_.vs.type = gapi::ShaderType::VERT;
  //       materialPtr->shaderCreateInfoSet_.vs.code = content;

  //       printf("TR: %s\n", materialPtr->shaderCreateInfoSet_.vs.code.c_str());
  //     },
  //     onShaderErrorRequest);

  shaderCreateInfoSet_.vs.type = gapi::ShaderType::VERT;
  shaderCreateInfoSet_.vs.code = "#version 300 es\n"
                                 "layout (location = 0) in vec3 attrib_pos;\n"
                                 "layout (location = 1) in vec2 attrib_texcoord_0;\n"
                                 "uniform mat4 mat_proj;\n"
                                 "uniform mat4 mat_model;\n"
                                 "out vec2 texcoord_0;\n"
                                 "void main() {\n"
                                 "  mat4 modelview = mat_proj * mat_model;\n"
                                 "  gl_Position = modelview * vec4(attrib_pos, 1.0);\n"
                                 "  texcoord_0 = attrib_texcoord_0;\n"
                                 "}";
}

void Material::loadFShaderFromFile(const std::string &filename) {
  // emscripten_async_wget_data(
  //     filename.c_str(), this,
  //     [](void *arg, void *buffer, int size) -> void {
  //       auto *materialPtr = (Material *)arg;
  //       auto content = materialPtr->onLoadVSFromFile(buffer, size);

  //       materialPtr->shaderCreateInfoSet_.fs.type = gapi::ShaderType::FRAG;
  //       materialPtr->shaderCreateInfoSet_.fs.code = content;
  //     },
  //     onShaderErrorRequest);

  shaderCreateInfoSet_.fs.type = gapi::ShaderType::FRAG;
  shaderCreateInfoSet_.fs.code =
      "#version 300 es\n"
      "#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
      "  precision highp float;\n"
      "#else\n"
      "  precision mediump float;\n"
      "#endif\n"
      "in vec2 texcoord_0;\n"
      "uniform sampler2D diffuse_sampler;\n"
      "uniform float time;\n"
      "out vec4 outcolor;\n"
      "void main() {\n"
      "  vec4 texcolor = texture(diffuse_sampler, vec2(texcoord_0.x + time, texcoord_0.y));\n"
      "  if(texcolor.a < 0.1) {\n"
      "    discard;\n"
      "  }\n"
      "  outcolor = texcolor;\n"
      "}";
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
