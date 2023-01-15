#include <sway/graphics/material.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Material::Material(std::shared_ptr<rms::ResourceManagerSystem> resmgr)
    : resmgr_(resmgr)
    , effect_(nullptr)
    , ambient_(0.0, 0.0, 0.0, 1.0)
    , diffuse_(0.0, 0.0, 0.0, 1.0)
    , specular_(0.0, 0.0, 0.0, 1.0)
    , emissive_(0.0, 0.0, 0.0, 1.0)
    , shininess_(0.0) {}

auto Material::loadImage(const std::string &name) -> bool {
  auto resource = resmgr_->findLoadedResource(name);

  auto image = std::make_shared<render::Image>(
      resource->getDescriptor().data, resource->getDescriptor().size.getW(), resource->getDescriptor().size.getH());
  images_.push_back(image);

  return true;
}

auto Material::loadEffect(const std::string &name) -> bool {
  gapi::ShaderCreateInfoSet shaderCreateInfoSet;
  shaderCreateInfoSet.vs.type = gapi::ShaderType::VERT;
  shaderCreateInfoSet.vs.code = "attribute vec3 attrib_pos;"
                                // "attribute vec4 attrib_col;"
                                "attribute vec2 attrib_texcoord_0;"
                                "uniform mat4 proj_mat;"
                                // "varying vec4 color;"
                                "varying vec2 texcoord_0;"
                                "void main() {"
                                "	gl_Position = proj_mat * vec4(attrib_pos, 1.0);"
                                // "	color = attrib_col;"
                                "	texcoord_0 = attrib_texcoord_0;"
                                "}";
  shaderCreateInfoSet.fs.type = gapi::ShaderType::FRAG;
  shaderCreateInfoSet.fs.code =
      // "varying vec4 color;"
      "varying vec2 texcoord_0;"
      "uniform sampler2D diffuse_sampler;"
      "uniform float time;"
      "void main() {"
      // "	gl_FragColor = color;"
      // " gl_FragColor = texture2D(diffuse_sampler, texcoord_0);"
      " gl_FragColor = texture2D(diffuse_sampler, vec2(texcoord_0.x + time, texcoord_0.y));"
      "}";

  effect_ = std::make_shared<render::Effect>(shaderCreateInfoSet);

  return true;
}

void Material::bind() {
  // effect_->getShaderProgram()->setUniformCol4f("mat_ambient", ambient_);
  // effect_->getShaderProgram()->setUniformCol4f("mat_diffuse", diffuse_);
  // effect_->getShaderProgram()->setUniformCol4f("mat_specular", specular_);
  // effect_->getShaderProgram()->setUniformCol4f("mat_emissive", emissive_);
  //  // effect_->getShaderProgram()->setUniform1f("mat_shininess", shininess_);

  effect_->getShaderProgram()->setUniform1i("diffuse_sampler", images_[0]->getTexture()->getUid().value());

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

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
