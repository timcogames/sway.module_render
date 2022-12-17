#include <sway/graphics/drawable.hpp>
#include <sway/graphics/material.hpp>
#include <sway/graphics/rendersubsystem.hpp>
#include <sway/graphics/vertexchannel.hpp>
#include <sway/graphics/vertexdata.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)

Drawable::Drawable(const GeometryCreateInfo &info, MaterialRef_t material, bool indexed)
    : geometryCreateInfo_(info)
    , vbuffer_(nullptr)
    , ibuffer_(nullptr)
    , vlayout_(nullptr)
    , material_(material)
    , indexed_(indexed) {}

void Drawable::create(VertexDataRef_t vertexData) {
  auto *pluginFuncSet = global::getGapiFunctionSet();

  idGenerator_ = pluginFuncSet->createIdGenerator();

  if (geometryCreateInfo_.vb.data != nullptr) {
    vbuffer_ = pluginFuncSet->createBuffer(idGenerator_, geometryCreateInfo_.vb);
  }

  if (geometryCreateInfo_.ib.data != nullptr && indexed_) {
    ibuffer_ = pluginFuncSet->createBuffer(idGenerator_, geometryCreateInfo_.ib);
  }

  vlayout_ = pluginFuncSet->createVertexAttribLayout(material_->getShaderProgram());
  for (const auto &channel : vertexData->getChannels()) {
    vlayout_->addAttribute(channel.second->getVertexAttribDescriptor());
  }
}

auto Drawable::getTopology() const -> gapi::TopologyType { return geometryCreateInfo_.topology; }

NAMESPACE_END(graphics)
NAMESPACE_END(sway)
