#include <sway/graphics/drawable.hpp>
#include <sway/graphics/material.hpp>
#include <sway/graphics/rendersubsystem.hpp>
#include <sway/graphics/vertexchannel.hpp>
#include <sway/graphics/vertexdata.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Drawable::Drawable(MaterialRef_t material, bool indexed)
    : vbuffer_(nullptr)
    , ibuffer_(nullptr)
    , vlayout_(nullptr)
    , material_(material)
    , indexed_(indexed) {}

void Drawable::create(VertexDataRef_t vertexData, const gapi::BufferCreateInfoSet &infoSet) {
  auto *pluginFuncSet = global::getGapiFunctionSet();

  auto idQueue = pluginFuncSet->createBufferIdQueue();

  if (infoSet.vb.data != nullptr) {
    vbuffer_ = pluginFuncSet->createBuffer(idQueue, infoSet.vb);
  }

  if (infoSet.ib.data != nullptr && indexed_) {
    ibuffer_ = pluginFuncSet->createBuffer(idQueue, infoSet.ib);
  }

  vlayout_ = pluginFuncSet->createVertexLayout(material_->getShaderProgram());
  for (const auto &channel : vertexData->getChannels()) {
    vlayout_->addAttribute(channel.second->getVertexAttribDescriptor());
  }
}

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
