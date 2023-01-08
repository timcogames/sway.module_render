#include <sway/graphics/material.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Material::Material()
    : effect_(nullptr)
    , ambient_(0.0, 0.0, 0.0, 1.0)
    , diffuse_(0.0, 0.0, 0.0, 1.0)
    , specular_(0.0, 0.0, 0.0, 1.0)
    , emissive_(0.0, 0.0, 0.0, 1.0)
    , shininess_(0.0) {}

auto Material::loadImage(const std::string &resourceName) -> bool { return true; }

auto Material::loadEffect(const std::string &resourceName) -> bool {
  gapi::ShaderCreateInfoSet shaderCreateInfoSet;
  shaderCreateInfoSet.vs.type = gapi::ShaderType::VERT;
  shaderCreateInfoSet.vs.code = "attribute vec3 attrib_pos;"
                                "attribute vec4 attrib_col;"
                                "uniform mat4 proj_mat;"
                                "varying vec4 color;"
                                "void main() {"
                                "	gl_Position = proj_mat * vec4(attrib_pos, 1.0);"
                                "	color = attrib_col;"
                                "}";
  shaderCreateInfoSet.fs.type = gapi::ShaderType::FRAG;
  shaderCreateInfoSet.fs.code = "varying vec4 color;"
                                "void main() {"
                                "	gl_FragColor = color;"
                                "}";

  effect_ = std::make_shared<render::Effect>(shaderCreateInfoSet);

  return true;
}

void Material::bind() {
  effect_->getShaderProgram()->setUniformCol4f("mat_ambient", ambient_);
  effect_->getShaderProgram()->setUniformCol4f("mat_diffuse", diffuse_);
  effect_->getShaderProgram()->setUniformCol4f("mat_specular", specular_);
  effect_->getShaderProgram()->setUniformCol4f("mat_emissive", emissive_);
  // effect_->getShaderProgram()->setUniform1f("mat_shininess", shininess_);

  effect_->bind();
}

void Material::unbind() { effect_->unbind(); }

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
