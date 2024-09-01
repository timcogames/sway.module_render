#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geombuilder.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Geom::Geom(global::GapiPluginFunctionSet *plug, GeomBuilder *builder)
    : core::foundation::Uniqueable<std::string>(core::misc::newGuid<UUID_NBR_OF_GROUPS>(UUID_MAGIC))
    , gapiPlugin_(plug)
    , builder_(builder)
    , attribLayout_(nullptr) {}

Geom::~Geom() {
  std::fill(buffers_.begin(), buffers_.end(), std::nullopt);
  // SAFE_DELETE_OBJECT(attribLayout_);
  builder_->stats_.numGeoms -= 1;
}

void Geom::create(const GeometryCreateInfo &info, Effect::Ptr_t effect,
    std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs) {

  attribs_ = attribs;

  attribLayout_ = gapiPlugin_->createVertexAttribLayout(effect->getShaderProgram());
  for (const auto &attrib : attribs) {
    auto attribDesc = attrib.second->getDescriptor();
    if (!attribDesc.enabled) {
      continue;
    }

    attribLayout_->addAttribute(attribDesc);
  }

  auto createBuffers = [&, next = 0](std::optional<gapi::BufferPtr_t> &buf) mutable {
    if (next == Constants::IDX_EBO && !info.indexed) {
      return;
    }

    buf = std::make_optional<gapi::BufferPtr_t>(gapiPlugin_->createBuffer(builder_->getIdGenerator(), info.bo[next]));
    ++next;
  };

  std::for_each(buffers_.begin(), buffers_.end(), createBuffers);
  builder_->stats_.numGeoms += 1;
}

void Geom::bind() {
  this->call<gapi::BufferPtr_t>(gapi::Buffer::BindFunctor());
  attribLayout_->enable();
}

void Geom::unbind() {
  attribLayout_->disable();
  this->call<gapi::BufferPtr_t>(gapi::Buffer::UnbindFunctor());
}

void Geom::updateUV(std::vector<UVData2> uv) {
  auto offset = 0;

  auto vboCapacity = buffers_[Constants::IDX_VBO].value()->getCapacity();
  auto vtxdata = (void *)malloc(sizeof(math::VertexTexCoord) * vboCapacity);

  auto texIdx = 0;
  auto currRile = 0;

  for (auto i = 0; i < vboCapacity; i++) {
    for (auto const [_, attrib] : attribs_) {
      if (attrib->enabled()) {
        auto desc = attrib->getDescriptor();
        if (desc.semantic == gapi::VertexSemantic::TEXCOORD_0) {
          if (texIdx >= QUAD_TEXCOORD_SIZE2) {
            texIdx = 0;
            currRile++;
          }

          attrib->importRawdata2(vtxdata, offset, uv[currRile].uv[texIdx].asDataPtr());
          texIdx++;
        } else {
          attrib->getData(vtxdata, offset, i);
        }

        offset += desc.numComponents;
      }
    }
  }

  buffers_[Constants::IDX_VBO].value()->updateSubdata(vtxdata);
}

void Geom::setUV(int index, std::array<math::vec2f_t, 4> coords) {
  auto offset = 0;

  auto vboCapacity = buffers_[Constants::IDX_VBO].value()->getCapacity();  // Количество вершин
  auto vtxdata = (void *)malloc(sizeof(math::VertexTexCoord) * buffers_[Constants::IDX_VBO].value()->getCapacity());

  auto texIdx = 0;
  auto curTile = 0;

  for (auto i = 0; i < vboCapacity; ++i) {
    for (auto [_, attrib] : attribs_) {
      if (attrib->enabled()) {
        auto desc = attrib->getDescriptor();
        if (desc.semantic == gapi::VertexSemantic::POS) {
          attrib->getData(vtxdata, offset, i);
        }

        if (desc.semantic == gapi::VertexSemantic::COL) {
          attrib->getData(vtxdata, offset, i);
        }

        if (desc.semantic == gapi::VertexSemantic::TEXCOORD_0) {
          if (texIdx >= QUAD_TEXCOORD_SIZE2) {
            texIdx = 0;
            curTile++;
          }

          if (curTile == index) {
            static_pointer_cast<GeomVertexAttrib<math::vec2f_t>>(attrib)->setData(i, coords[texIdx].asDataPtr());

            attrib->getData(vtxdata, offset, i);
          } else {
            attrib->getData(vtxdata, offset, i);
          }

          texIdx++;
        }

        offset += desc.numComponents;
      }
    }
  }

  buffers_[Constants::IDX_VBO].value()->updateSubdata(vtxdata);
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
