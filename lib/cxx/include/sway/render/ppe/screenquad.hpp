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

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

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

    //  core::detail::EnumClassBitset<Flipper> flips;
    //     shape->setPosDataAttrib(
    //         Flippable::asRect(math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F).offset(-0.5F, -0.5F), flips), 2.0f);
    shape->setPosDataAttrib(/*math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F).offset(0.0F, 0.0F), */ 30.0F /*ZINDEX*/);
    // shape->setColDataAttrib(COL4F_WHITE);
    // shape->setTexDataAttrib(math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F));

    GeometryCreateInfo geomCreateInfo;
    geomCreateInfo.indexed = false;
    geomCreateInfo.topology = gapi::TopologyType::TRIANGLE_STRIP;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::STATIC;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexPosition);
    geomCreateInfo.bo[Constants::IDX_VBO].desc.capacity = 4;
    auto data = new f32_t[4 * sizeof(math::VertexPosition)];
    shape->data()->getVertices(data, 0, 4);
    geomCreateInfo.bo[Constants::IDX_VBO].data = data;

    // auto offset = 0;
    // for (auto i = 0; i < 4; i++) {
    //   std::cout << math::vec3f_t(data[offset + 0], data[offset + 1], data[offset + 2]) << std::endl;
    //   std::cout << math::vec4f_t(data[offset + 3], data[offset + 4], data[offset + 5], data[offset + 6]) <<
    //   std::endl; offset += 7;
    // }

    geomCreateInfo.bo[Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
    geomCreateInfo.bo[Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
    geomCreateInfo.bo[Constants::IDX_EBO].desc.capacity = 6;
    geomCreateInfo.bo[Constants::IDX_EBO].data = shape->data()->getElements();

    // for (auto i = 0; i < 6; i++) {
    //   std::cout << ((u32_t *)geomCreateInfo.bo[Constants::IDX_EBO].data)[i] << std::endl;
    // }

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
    cmd.geom = geom;
    cmd.topology = gapi::TopologyType::TRIANGLE_STRIP;
    cmd.mtrl = material_;
    cmd.tfrm = cmd.proj = cmd.view = math::mat4f_t();

    matrixStack_->push<math::MatrixType::PROJ>(cmd.proj);
    matrixStack_->push<math::MatrixType::VIEW>(cmd.view);
    matrixStack_->push<math::MatrixType::TFRM>(cmd.tfrm);

    cmd.mtrl->bind(matrixStack_);

    if (cmd.geom != nullptr) {
      cmd.geom->bind();

      gapi::BufferSet bufset;
      if (cmd.geom->getBuffer(Constants::IDX_VBO).has_value()) {
        bufset.vbo = cmd.geom->getBuffer(Constants::IDX_VBO).value();
      }

      if (cmd.geom->getBuffer(Constants::IDX_EBO).has_value()) {
        bufset.ebo = cmd.geom->getBuffer(Constants::IDX_EBO).value();
      } else {
        bufset.ebo = nullptr;
      }

      drawCall_->execute(cmd.topology, bufset, core::ValueDataType::UINT);

      cmd.geom->unbind();
    }

    cmd.mtrl->unbind();

    matrixStack_->pop<math::MatrixType::TFRM>();
    matrixStack_->pop<math::MatrixType::PROJ>();
    matrixStack_->pop<math::MatrixType::VIEW>();
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

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PPE_SCREENQUAD_HPP
