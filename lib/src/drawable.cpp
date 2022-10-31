#include <sway/graphics/drawable.hpp>
#include <sway/graphics/material.hpp>
#include <sway/graphics/rendersubsystem.hpp>
#include <sway/graphics/vertexchannel.hpp>
#include <sway/graphics/vertexdata.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Drawable::Drawable(MaterialRef_t material, bool indexed)
    : vbo_(nullptr)
    , ibo_(nullptr)
    , vlayout_(nullptr)
    , material_(material)
    , indexed_(indexed) {
  // Empty
}

Drawable::~Drawable() {
  // Empty
}

void Drawable::create(VertexDataRef_t vertexData, const gapi::BufferCreateInfoSet &infoSet) {
  auto *pluginFuncSet = global::getGapiFunctionSet();

  if (infoSet.vb.data != nullptr) {
    vbo_ = pluginFuncSet->createBuffer(infoSet.vb);
  }

  if (infoSet.ib.data != nullptr && indexed_) {
    ibo_ = pluginFuncSet->createBuffer(infoSet.ib);
  }

  vlayout_ = pluginFuncSet->createVertexLayout(material_->getShaderProgram());
  for (const auto &channel : vertexData->getChannels()) {
    vlayout_->addAttribute(channel.second->getVertexAttribDescriptor());
  }
}

gapi::BufferRef_t Drawable::getVBO() { return vbo_; }

gapi::BufferRef_t Drawable::getIBO() { return ibo_; }

gapi::VertexLayoutRef_t Drawable::getVertexLayout() { return vlayout_; }

MaterialRef_t Drawable::getMaterial() { return material_; }

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
