#include <sway/render/effect.hpp>
#include <sway/render/geometry.hpp>
#include <sway/render/global.hpp>
#include <sway/render/procedurals/shape.hpp>
#include <sway/render/rendersubsystem.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Geometry::Geometry(gapi::IdGeneratorPtr_t idgen, EffectRef_t effect, bool indexed)
    : idGenerator_(idgen)
    , attribLayout_(nullptr)
    , effect_(effect)
    , indexed_(indexed) {
  // std::cout << std::boolalpha << "Position: " << CustomVertex::hasPosition() << std::endl;
  // std::cout << std::boolalpha << "Color: " << CustomVertex::hasColor() << std::endl;
  // std::cout << std::boolalpha << "TexCoord: " << CustomVertex::hasTexCoord() << std::endl;
}

void Geometry::createArray(std::shared_ptr<procedurals::Shape> prim) {
  auto *pluginFuncSet = global::getGapiPluginFunctionSet();
  bufset_.vao = pluginFuncSet->createVertexArray();
  this->create(prim);
}

void Geometry::create(std::shared_ptr<procedurals::Shape> prim) {
  auto *pluginFuncSet = global::getGapiPluginFunctionSet();

  attribs_ = prim->getVertexAttribs();
  attribLayout_ = pluginFuncSet->createVertexAttribLayout(effect_->getShaderProgram());
  for (const auto &attrib : attribs_) {
    attribLayout_->addAttribute(attrib.second->getDescriptor());
  }

  info_ = prim->getGeometryInfo();

  // info_.bo[IDX_VBO].desc.target = gapi::BufferTarget::ARRAY;
  bufset_.vbo = pluginFuncSet->createBuffer(idGenerator_, info_.bo[Constants::IDX_VBO]);

  if (indexed_) {
    // info_.bo[IDX_EBO].desc.target = gapi::BufferTarget::ELEMENT_ARRAY;
    bufset_.ebo = pluginFuncSet->createBuffer(idGenerator_, info_.bo[Constants::IDX_EBO]);
  }
}

void Geometry::updateUV(std::vector<UVData> uv, const math::size2i_t &segments) {
  auto offset = 0;
  auto *vtxdata = (void *)malloc(sizeof(math::VertexTexCoord) * info_.bo[Constants::IDX_VBO].desc.capacity);

  auto texIdx = 0;
  auto currRile = 0;

  for (auto i = 0; i < info_.bo[Constants::IDX_VBO].desc.capacity; ++i) {
    for (auto const [_, attrib] : attribs_) {
      if (attrib->isEnabled()) {
        auto desc = attrib->getDescriptor();
        if (desc.semantic == gapi::VertexSemantic::TEXCOORD_0) {
          if (texIdx >= QUAD_TEXCOORD_SIZE) {
            texIdx = 0;
            currRile++;
          }

          attrib->importRawdata2(vtxdata, offset, uv[currRile].uv[texIdx].data());

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

void Geometry::setUV(int index, std::array<math::vec2f_t, 4> coords) {
  auto offset = 0;
  auto *vtxdata = (void *)malloc(sizeof(math::VertexTexCoord) * info_.bo[Constants::IDX_VBO].desc.capacity);

  auto texIdx = 0;
  auto curTile = 0;

  for (auto i = 0; i < info_.bo[Constants::IDX_VBO].desc.capacity /* количество вершин */; ++i) {
    for (auto [_, attrib] : attribs_) {
      if (attrib->isEnabled()) {
        auto desc = attrib->getDescriptor();
        if (desc.semantic == gapi::VertexSemantic::POS) {
          attrib->importRawdata(vtxdata, offset, i);
        }

        if (desc.semantic == gapi::VertexSemantic::COL) {
          attrib->importRawdata(vtxdata, offset, i);
        }

        if (desc.semantic == gapi::VertexSemantic::TEXCOORD_0) {
          if (texIdx >= QUAD_TEXCOORD_SIZE) {
            texIdx = 0;
            curTile++;
          }

          if (curTile == index) {
            static_pointer_cast<GeometryVertexAttrib<math::vec2f_t>>(attrib)->setVertexData(i, coords[texIdx].data());

            attrib->importRawdata(vtxdata, offset, i);
          } else {
            attrib->importRawdata(vtxdata, offset, i);
          }

          texIdx++;
        }

        offset += desc.numComponents;
      }
    }
  }

  bufset_.vbo->updateSubdata(vtxdata);
}

// void Geometry::setUV(int index, std::array<math::vec2f_t, 4> coords) {
//   auto offset = 0;
//   auto *vtxdata = (void *)malloc(sizeof(math::VertexTexCoord) * info_.bo[IDX_VBO].desc.capacity);

//   auto texIdx = 0;
//   auto curTile = 0;

//   for (auto i = 0; i < info_.bo[IDX_VBO].desc.capacity /* количество вершин */; ++i) {
//     for (auto [_, attrib] : attribs_) {
//       if (attrib->isEnabled()) {
//         auto desc = attrib->getDescriptor();
//         if (desc.semantic == gapi::VertexSemantic::POS) {
//           attrib->importRawdata(vtxdata, offset, i);

//           std::cout << "POS " << i << " = " << *((f32_t *)attrib->getComponent(i)) << std::endl;
//         }

//         if (desc.semantic == gapi::VertexSemantic::COL) {
//           attrib->importRawdata(vtxdata, offset, i);

//           std::cout << "COL " << i << " = " << *((f32_t *)attrib->getComponent(i)) << std::endl;
//         }

//         if (desc.semantic == gapi::VertexSemantic::TEXCOORD_0) {
//           attrib->importRawdata(vtxdata, offset, i);

//           std::cout << "TEX " << i << " = " << *((f32_t *)attrib->getComponent(i)) << std::endl;
//         }

//         offset += desc.numComponents;
//       }
//     }
//   }

//   bufset_.vbo->updateSubdata(vtxdata);
// }

void Geometry::bind() {
  if (bufset_.vao) {
    bufset_.vao->bind();
  }

  if (bufset_.vbo) {
    bufset_.vbo->bind();
  }

  attribLayout_->enable();

  if (bufset_.ebo) {
    bufset_.ebo->bind();
  }
}

void Geometry::unbind() {
  if (bufset_.ebo) {
    bufset_.ebo->unbind();
  }

  attribLayout_->disable();

  if (bufset_.vbo) {
    bufset_.vbo->unbind();
  }

  if (bufset_.vao) {
    bufset_.vao->unbind();
  }
}

auto Geometry::getTopology() const -> gapi::TopologyType { return info_.topology; }

NAMESPACE_END(render)
NAMESPACE_END(sway)
