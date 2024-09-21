#ifndef SWAY_RENDER_PPE_FULLSCREENQUADRILATERAL_HPP
#define SWAY_RENDER_PPE_FULLSCREENQUADRILATERAL_HPP

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
#include <sway/render/rendersubqueue.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class FullscreenQuadrilateral : public RenderComponent {
  DECLARE_CLASS_METADATA(FullscreenQuadrilateral, RenderComponent)
  DECLARE_CLASS_POINTER_ALIASES(FullscreenQuadrilateral)

public:
#pragma region "Ctors/Dtor"

  FullscreenQuadrilateral() = default;

  ~FullscreenQuadrilateral() { geomBuilder_->remove(geomIdx_); }

#pragma endregion

  void initialize(core::misc::Dictionary glob, GeomBuilder::SharedPtr_t geomBuilder,
      RenderSubqueue::SharedPtr_t subqueue, Material::SharedPtr_t material) {
    geomBuilder_ = geomBuilder;
    subqueue_ = subqueue;
    material_ = material;

    screenWdt_ = (f32_t)glob.getIntegerOrDefault("screen_wdt", 800);
    screenHgt_ = (f32_t)glob.getIntegerOrDefault("screen_hgt", 600);

    auto shape = new procedurals::prims::Quadrilateral<math::VertexTexCoord>(
        {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0});

    //  core::detail::EnumClassBitset<Flipper> flips;
    //     shape->setPosDataAttrib(
    //         Flippable::asRect(math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F).offset(-0.5F, -0.5F), flips), 2.0f);
    shape->setPosDataAttrib(/*math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F).offset(0.0F, 0.0F), */ 30.0F /*ZINDEX*/);
    shape->setColDataAttrib(COL4F_WHITE);
    shape->setTexDataAttrib(math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F));

    GeometryCreateInfo geomCreateInfo;
    geomCreateInfo.indexed = true;
    geomCreateInfo.topology = gapi::TopologyType::TRIANGLE_LIST;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::STATIC;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexTexCoord);
    geomCreateInfo.bo[Constants::IDX_VBO].desc.capacity = 4;
    auto data = new f32_t[4 * sizeof(math::VertexTexCoord)];
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

    geomIdx_ = geomBuilder_->create<procedurals::prims::Quadrilateral<math::VertexTexCoord>>(
        geomCreateInfo, shape->getVertexAttribs(), material_->getEffect());
  }

#pragma region "Override RenderComponent methods"

  MTHD_OVERRIDE(void onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, f32_t dtm)) {
    auto geom = geomBuilder_->getGeometry(geomIdx_);
    if (!geom) {
      return;
    }

    pipeline::ForwardRenderCommand cmd;
    cmd.stage = 0;
    cmd.blendDesc.enabled = false;
    cmd.depthDesc.enabled = false;
    cmd.stencilDesc.enabled = false;
    cmd.geom = geom;
    cmd.topology = gapi::TopologyType::TRIANGLE_LIST;
    cmd.mtrl = material_;

    // clang-format off
    cmd.tfrm = math::mat4f_t();
    cmd.proj.setData(math::Projection((struct math::ProjectionDescription) {
      .rect = {{ -1.0F, -1.0F, 1.0F, 1.0F }},
      .fov = 0,
      .aspect = screenWdt_ / screenHgt_,
      .znear = 1.0F,
      .zfar = 10.0F
    }).makeOrtho());
    cmd.view = math::mat4f_t();
    // clang-format on
    subqueue_->post(cmd);
  }

#pragma endregion

  [[nodiscard]]
  auto getMaterial() const -> Material::SharedPtr_t {
    return material_;
  }

private:
  RenderSubqueue::SharedPtr_t subqueue_;
  Material::SharedPtr_t material_;
  GeomBuilder::SharedPtr_t geomBuilder_;
  u32_t geomIdx_;

  f32_t screenWdt_;
  f32_t screenHgt_;
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PPE_FULLSCREENQUADRILATERAL_HPP
