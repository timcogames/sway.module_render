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

  info_ = prim->getGeometryInfo();

  info_.vb.desc.target = gapi::BufferTarget::ARRAY;
  bufset_.vbo = pluginFuncSet->createBuffer(idGenerator_, info_.vb);

  if (indexed_) {
    info_.ib.desc.target = gapi::BufferTarget::ELEMENT_ARRAY;
    bufset_.ibo = pluginFuncSet->createBuffer(idGenerator_, info_.ib);
  }

  vtxArray_ = pluginFuncSet->createVertexArray();
}

void Geometry::updateUV(std::vector<UVData> uv, const math::size2i_t &segments) {
  s32_t offset = 0;
  void *vtxdata = (void *)malloc(sizeof(math::VertexTexCoord) * info_.vb.desc.capacity);

  auto texIdx = 0;
  auto currRile = 0;

  for (auto i = 0; i < info_.vb.desc.capacity; ++i) {
    for (auto const [_, attrib] : vtxAttribs_) {
      if (attrib->isEnabled()) {
        auto desc = attrib->getDescriptor();
        if (desc.semantic == gapi::VertexSemantic::TEXCOORD_0) {
          if (texIdx >= 4) {
            texIdx = 0;
            currRile++;
          }

          attrib->importRawdata2(vtxdata, offset, uv[currRile].uv[texIdx].getData().data());

          texIdx++;

          // auto width = segments.getW() + 1;
          // auto col = i % width;
          // auto row = i / width;

        } else {
          attrib->importRawdata(vtxdata, offset, i);
        }

        offset += desc.numComponents;
      }
    }
  }

  bufset_.vbo->updateSubdata(vtxdata);
}

void Geometry::bind() {
  vtxArray_->bind();

  bufset_.vbo->bind();
  vtxAttribLayout_->enable();

  if (bufset_.ibo) {
    bufset_.ibo->bind();
  }
}

void Geometry::unbind() {
  if (bufset_.ibo) {
    bufset_.ibo->unbind();
  }

  vtxAttribLayout_->disable();
  bufset_.vbo->unbind();

  vtxArray_->unbind();
}

auto Geometry::getTopology() const -> gapi::TopologyType { return info_.topology; }

NAMESPACE_END(render)
NAMESPACE_END(sway)
