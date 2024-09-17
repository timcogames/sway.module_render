#ifndef SWAY_RENDER_PPE_FULLSCREENQUADRILATERAL_HPP
#define SWAY_RENDER_PPE_FULLSCREENQUADRILATERAL_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/render/flippable.hpp>
#include <sway/render/flipper.hpp>
#include <sway/render/material.hpp>
#include <sway/render/pipeline/rendercommand.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/procedurals/prims/quadrilateralstrip.hpp>
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

  void initialize(
      GeomBuilder::SharedPtr_t geomBuilder, RenderSubqueue::SharedPtr_t subqueue, Material::SharedPtr_t material) {
    geomBuilder_ = geomBuilder;
    subqueue_ = subqueue;
    material_ = material;

    // auto shape = new procedurals::prims::QuadrilateralStrip<math::VertexTexCoord>(
    //     {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0}, math::size2i_t(1));
    auto shape = new procedurals::prims::QuadrilateralStrip<math::VertexColor>(
        {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL}, math::size2i_t(1));

    //  core::detail::EnumClassBitset<Flipper> flips;
    //     shape->setPosDataAttrib(
    //         Flippable::asRect(math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F).offset(-0.5F, -0.5F), flips), 2.0f);
    shape->setPosDataAttrib(math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F).offset(-0.5F, -0.5F), 2.0f);
    shape->setColDataAttrib(COL4F_WHITE);
    // shape->setTexDataAttrib(math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F));

    GeometryCreateInfo geomCreateInfo;
    geomCreateInfo.indexed = true;
    geomCreateInfo.topology = gapi::TopologyType::TRIANGLE_STRIP;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::STATIC;
    geomCreateInfo.bo[Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexColor);
    geomCreateInfo.bo[Constants::IDX_VBO].desc.capacity = shape->getReserveVerts();
    auto data = new f32_t[shape->getReserveVerts() * sizeof(math::VertexColor)];
    shape->data()->getVertices(data, 0, shape->getReserveVerts());
    geomCreateInfo.bo[Constants::IDX_VBO].data = data;

    geomCreateInfo.bo[Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
    geomCreateInfo.bo[Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
    geomCreateInfo.bo[Constants::IDX_EBO].desc.capacity = shape->getReserveElems();
    geomCreateInfo.bo[Constants::IDX_EBO].data = shape->data()->getElements();

    geomIdx_ = geomBuilder_->create<procedurals::prims::QuadrilateralStrip<math::VertexColor>>(
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
    cmd.topology = gapi::TopologyType::TRIANGLE_STRIP;
    cmd.material = material_;
    // cmd.tfrm = tfrm;
    // cmd.proj = proj;
    // cmd.view = view;

    // clang-format off
    cmd.tfrm = math::mat4f_t();
    cmd.proj.setData(math::Projection((struct math::ProjectionDescription) {
      .rect = {{ -1.0F /* L */, -1.0F /* B->T */, 1.0F /* R */, 1.0F /* T->B */ }},
      .fov = 0,
      .aspect = 800.0F / 600.0F,
      .znear = 1.0F,
      .zfar = 10.0F
    }).makeOrtho());
    cmd.view = math::xform3f_t::translate(cmd.view, 0.0F, 0.0F, 0.0F);
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
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PPE_FULLSCREENQUADRILATERAL_HPP
