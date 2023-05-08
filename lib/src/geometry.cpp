#include <sway/render/effect.hpp>
#include <sway/render/geometry.hpp>
#include <sway/render/global.hpp>
#include <sway/render/procedurals/shape.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Geometry::Geometry(std::shared_ptr<gapi::IdGenerator> idgen, EffectRef_t effect, bool indexed)
    : idGenerator_(idgen)
    , vtxAttribLayout_(nullptr)
    , vtxArray_(nullptr)
    , vtxBuffer_(nullptr)
    , idxBuffer_(nullptr)
    , effect_(effect)
    , indexed_(indexed) {
  // std::cout << std::boolalpha << "Position: " << CustomVertex::hasPosition() << std::endl;
  // std::cout << std::boolalpha << "Color: " << CustomVertex::hasColor() << std::endl;
  // std::cout << std::boolalpha << "TexCoord: " << CustomVertex::hasTexCoord() << std::endl;
}

void Geometry::create(std::shared_ptr<procedurals::Shape> prim) {
  auto *pluginFuncSet = global::getGapiFunctionSet();

  vtxAttribs_ = prim->getVertexAttribs();
  vtxAttribLayout_ = pluginFuncSet->createVertexAttribLayout(effect_->getShaderProgram());
  for (const auto &attrib : vtxAttribs_) {
    vtxAttribLayout_->addAttribute(attrib.second->getDescriptor());
  }

  // vtxArray_ = pluginFuncSet->createVertexArray();
  info_ = prim->getGeometryInfo();

  info_.vb.desc.target = gapi::BufferTarget::ARRAY;
  vtxBuffer_ = pluginFuncSet->createBuffer(idGenerator_, info_.vb);

  if (indexed_) {
    info_.ib.desc.target = gapi::BufferTarget::ELEMENT_ARRAY;
    idxBuffer_ = pluginFuncSet->createBuffer(idGenerator_, info_.ib);
  }
}

void Geometry::updateUV(std::vector<math::vec2f_t> uv) {
  s32_t offset = 0;
  void *vtxdata = (void *)malloc(sizeof(math::VertexTexCoord) * 4);

  for (auto i = 0; i < 4; ++i) {
    for (auto const [_, attrib] : vtxAttribs_) {
      if (attrib->isEnabled()) {
        auto desc = attrib->getDescriptor();
        if (desc.semantic == gapi::VertexSemantic::TEXCOORD_0) {
          attrib->importRawdata2(vtxdata, offset, uv[i].getData().data());
        } else {
          attrib->importRawdata(vtxdata, offset, i);
        }

        offset += desc.numComponents;
      }
    }
  }

  vtxBuffer_->updateSubdata(vtxdata);
}

void Geometry::bind() {
  vtxBuffer_->bind();
  vtxAttribLayout_->enable();

  if (idxBuffer_) {
    idxBuffer_->bind();
  }
}

void Geometry::unbind() {
  if (idxBuffer_) {
    idxBuffer_->unbind();
  }

  vtxAttribLayout_->disable();
  vtxBuffer_->unbind();
}

auto Geometry::getTopology() const -> gapi::TopologyType { return info_.topology; }

NAMESPACE_END(render)
NAMESPACE_END(sway)
