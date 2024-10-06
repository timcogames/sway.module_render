#ifndef SWAY_RENDER_PPE_SCREENQUAD_HPP
#define SWAY_RENDER_PPE_SCREENQUAD_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/flippable.hpp>
#include <sway/render/flipper.hpp>
#include <sway/render/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/prims/quadrilateral.hpp>
#include <sway/render/rendercomponent.hpp>
#include <sway/render/renderqueue.hpp>
#include <sway/render/renderstages.hpp>
#include <sway/render/rendersubqueue.hpp>

#include <memory>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class ScreenQuad {
  DECLARE_CLASS_POINTER_ALIASES(ScreenQuad)

public:
#pragma region "Ctors/Dtor"

  ScreenQuad() {
    drawCall_ = global::getGapiPluginFunctionSet()->createDrawCall();
    matrixStack_ = std::make_shared<math::MatrixStack>();
  }

  ~ScreenQuad() { geomBuilder_->remove(geomIdx_); }

#pragma endregion

  void initialize(core::misc::Dictionary glob, GeomBuilder::SharedPtr_t geomBuilder, Material::SharedPtr_t material) {
    geomBuilder_ = geomBuilder;
    material_ = material;

    screenWdt_ = (f32_t)glob.getIntegerOrDefault("screen_wdt", 800);
    screenHgt_ = (f32_t)glob.getIntegerOrDefault("screen_hgt", 600);

    auto shape = new procedurals::prims::Quadrilateral<math::VertexPosition>({gapi::VertexSemantic::POS});

    shape->setPosDataAttrib(/*math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F).offset(0.0F, 0.0F), */ 30.0F /*ZINDEX*/);

    GeometryCreateInfo geomCreateInfo;
    geomCreateInfo.indexed = false;
    geomCreateInfo.topology = gapi::TopologyType::Enum::TRIANGLE_STRIP;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::Enum::STATIC;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexPosition);
    geomCreateInfo.bo[Constants::IDX_VBO].desc.capacity = 4;
    auto data = new f32_t[4 * sizeof(math::VertexPosition)];
    shape->data()->getVertices(data, 0, 4);
    geomCreateInfo.bo[Constants::IDX_VBO].data = data;

    geomIdx_ = geomBuilder_->create<procedurals::prims::Quadrilateral<math::VertexPosition>>(
        geomCreateInfo, shape->getVertexAttribs(), material_->getEffect());
  }

  void onUpdate(f32_t dtm) {
    auto geom = geomBuilder_->getGeometry(geomIdx_);
    if (!geom) {
      return;
    }

    pipeline::ForwardRenderCommand cmd;
    cmd.stage = core::detail::toBase(RenderStage::IDX_DEPTH);
    cmd.blendDesc.enabled = false;
    cmd.depthDesc.enabled = false;
    cmd.stencilDesc.enabled = false;
    cmd.topology = gapi::TopologyType::Enum::TRIANGLE_STRIP;
    cmd.geom = geom;
    cmd.mtrl = material_;
    cmd.tfrm = cmd.proj = cmd.view = math::mat4f_t();

    matrixStack_->push<math::MatrixType::Enum::PROJ>(cmd.proj);
    matrixStack_->push<math::MatrixType::Enum::VIEW>(cmd.view);
    matrixStack_->push<math::MatrixType::Enum::TFRM>(cmd.tfrm);

    cmd.mtrl->bind(matrixStack_);
    cmd.geom->bind();

    gapi::BufferSet bufset;
    bufset.vbo = cmd.geom->getBuffer(Constants::IDX_VBO).value();
    bufset.ebo = nullptr;

    drawCall_->execute(cmd.topology, bufset, core::ValueDataType::Enum::UINT);

    cmd.geom->unbind();
    cmd.mtrl->unbind();

    matrixStack_->pop<math::MatrixType::Enum::TFRM>();
    matrixStack_->pop<math::MatrixType::Enum::PROJ>();
    matrixStack_->pop<math::MatrixType::Enum::VIEW>();
  }

  [[nodiscard]]
  auto getMaterial() const -> Material::SharedPtr_t {
    return material_;
  }

private:
  gapi::DrawCallPtr_t drawCall_;
  std::shared_ptr<math::MatrixStack> matrixStack_;
  Material::SharedPtr_t material_;
  GeomBuilder::SharedPtr_t geomBuilder_;
  u32_t geomIdx_;

  f32_t screenWdt_;
  f32_t screenHgt_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PPE_SCREENQUAD_HPP
