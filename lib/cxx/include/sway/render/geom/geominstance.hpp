#ifndef SWAY_RENDER_GEOMINSTANCE_HPP
#define SWAY_RENDER_GEOMINSTANCE_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/geom/geom.hpp>
#include <sway/render/geom/geominstancedatadivisor.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class GeomBuilder;

template <typename TShape>
class GeomInstance : public Geom {
public:
  using ShapeVtxDataType_t = typename TShape::VtxDataType_t;

  GeomInstance(global::GapiPluginFunctionSet *plug, GeomBuilder *builder, GeomInstanceDataDivisor<TShape> *divisor)
      : Geom(plug, builder)
      , dataDivisor_(divisor)
      , data_(nullptr) {}

  virtual ~GeomInstance() {
    SAFE_DELETE_OBJECT(data_);
    SAFE_DELETE_OBJECT(vao_);
    SAFE_DELETE_OBJECT(dataDivisor_);
  }

  MTHD_OVERRIDE(void create(const GeometryCreateInfo &info, EffectPtr_t effect,
      std::map<gapi::VertexSemantic, std::shared_ptr<GeomVertexAttribBase>> attribs)) {
    vao_ = gapiPlugin_->createVertexArray();
    Geom::create(info, effect, attribs);
  }

  MTHD_OVERRIDE(void bind()) {
    vao_->bind();
    Geom::bind();
  }

  MTHD_OVERRIDE(void unbind()) {
    Geom::unbind();
    vao_->unbind();
  }

  template <typename TDataType, typename TMemFn = std::function<void *(void *, TDataType, std::size_t)>>
  void updateData(TMemFn callback, int offset, TDataType vertices, gapi::BufferPtr_t vbo,
      core::detail::EnumClassBitset<gapi::BufferMapRangeAccess> bitset) {
    data_ = (ShapeVtxDataType_t *)vbo->mapRange(
        offset, TShape::MAX_QUAD_RESERVE_VERTICES * sizeof(ShapeVtxDataType_t), bitset);
    callback(data_, vertices, TShape::MAX_QUAD_RESERVE_VERTICES * sizeof(ShapeVtxDataType_t));
    // vbo->flush(offset, TShape::MAX_QUAD_RESERVE_VERTICES * sizeof(ShapeVtxDataType_t));
    vbo->unmap();
  }

  void remap() {
    auto vbo = this->getBuffer(render::Constants::IDX_VBO);
    if (!vbo.has_value()) {
      std::cout << "[ERR]: IDX_VBO" << std::endl;
      return;
    }

    core::detail::EnumClassBitset<gapi::BufferMapRangeAccess> bitset;
    bitset.flip(gapi::BufferMapRangeAccess::WRITE);
    bitset.flip(gapi::BufferMapRangeAccess::INVALIDATE_BUFFER);
    // bitset.flip(gapi::BufferMapRangeAccess::FLUSH_EXPLICIT);

    // data_ = (ShapeVtxDataType_t *)vbo.value()->mapRange(
    //     0, (TShape::MAX_QUAD_RESERVE_VERTICES * sizeof(ShapeVtxDataType_t)) * dataDivisor_->getInstSize(), bitset);

    auto offset = 0;
    for (auto i = 0; i < dataDivisor_->getInstSize(); ++i) {
      auto inst = dataDivisor_->at(i);
      if (!inst->mustBeRemapped()) {
        updateData<int>(std::memset, offset, 0, vbo.value(), bitset);
      } else {
        void *vertices = malloc(TShape::MAX_QUAD_RESERVE_VERTICES * sizeof(ShapeVtxDataType_t));
        inst->data()->getVertices(vertices, 0, TShape::MAX_QUAD_RESERVE_VERTICES);
        updateData<const void *>(std::memcpy, offset, vertices, vbo.value(), bitset);
        free(vertices);
      }

      offset += TShape::MAX_QUAD_RESERVE_VERTICES * sizeof(ShapeVtxDataType_t);
    }

    // vbo.value()->unmap();
  }

  auto getDivisor() -> GeomInstanceDataDivisor<TShape> * { return dataDivisor_; }

private:
  gapi::VertexArrayPtr_t vao_;
  GeomInstanceDataDivisor<TShape> *dataDivisor_;
  ShapeVtxDataType_t *data_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_GEOMINSTANCE_HPP