#include <sway/gapi.hpp>
#include <sway/render/sprite.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

#define NUM_SEGMENTS 2

void Sprite::initialize(std::shared_ptr<RenderSubsystem> subsystem, std::shared_ptr<RenderSubqueue> subqueue,
    std::shared_ptr<Material> material, const math::size2f_t &size) {
  subqueue_ = subqueue;
  material_ = material;

  std::array<gapi::VertexSemantic, 2> semantics = {gapi::VertexSemantic::POS, gapi::VertexSemantic::TEXCOORD_0};
  auto plane = std::make_shared<procedurals::prims::Plane<math::VertexTexCoord>>(
      size, math::size2i_t(NUM_SEGMENTS, NUM_SEGMENTS));
  plane->useVertexSemanticSet(semantics);

  geometry_ = std::make_shared<Geometry>(subsystem->getIdGenerator(), material_->getEffect(), true);
  geometry_->create(plane);
}

void Sprite::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, [[maybe_unused]] f32_t dtime) {
  pipeline::ForwardRenderCommand cmd;
  cmd.stage = 0;
  cmd.depth.enabled = true;
  cmd.depth.func = gapi::CompareFunction::LESS;
  cmd.stencil.enabled = true;
  cmd.stencil.func = gapi::CompareFunction::ALWAYS;
  cmd.stencil.fail = gapi::StencilOperation::KEEP;
  cmd.stencil.depthFail = gapi::StencilOperation::KEEP;
  cmd.stencil.depthPass = gapi::StencilOperation::REPLACE;
  cmd.geometry = geometry_;
  cmd.material = material_;
  cmd.tfrm = tfrm;
  cmd.proj = proj;
  cmd.view = view;

  subqueue_->post(cmd);
}

// clang-format off
void Sprite::updateGeometryUV(math::size2f_t textureSize, math::rect4f_t frameRect) {
  // geometry_->updateUV({
  //   {{
  //     {(frameRect.getL() / textureSize.getW())*0.1F, (frameRect.getT() / textureSize.getH())*0.1F},
  //     {(frameRect.getR() / textureSize.getW())*0.1F, (frameRect.getT() / textureSize.getH())*0.1F},
  //     {(frameRect.getL() / textureSize.getW())*0.1F, (frameRect.getB() / textureSize.getH())*0.1F},
  //     {(frameRect.getR() / textureSize.getW())*0.1F, (frameRect.getB() / textureSize.getH())*0.1F}
  //   }},

  //   {{
  //     {frameRect.getL() / textureSize.getW(), frameRect.getT() / textureSize.getH()},
  //     {frameRect.getR() / textureSize.getW(), frameRect.getT() / textureSize.getH()},
  //     {frameRect.getL() / textureSize.getW(), frameRect.getB() / textureSize.getH()},
  //     {frameRect.getR() / textureSize.getW(), frameRect.getB() / textureSize.getH()}
  //   }},

  //   {{
  //     {frameRect.getL() / textureSize.getW(), frameRect.getT() / textureSize.getH()},
  //     {frameRect.getR() / textureSize.getW(), frameRect.getT() / textureSize.getH()},
  //     {frameRect.getL() / textureSize.getW(), frameRect.getB() / textureSize.getH()},
  //     {frameRect.getR() / textureSize.getW(), frameRect.getB() / textureSize.getH()}
  //   }},

  //   {{
  //     {frameRect.getL() / textureSize.getW(), frameRect.getT() / textureSize.getH()},
  //     {frameRect.getR() / textureSize.getW(), frameRect.getT() / textureSize.getH()},
  //     {frameRect.getL() / textureSize.getW(), frameRect.getB() / textureSize.getH()},
  //     {frameRect.getR() / textureSize.getW(), frameRect.getB() / textureSize.getH()}
  //   }}
  // }, math::size2i_t(NUM_SEGMENTS, NUM_SEGMENTS));
}  // clang-format on

NAMESPACE_END(render)
NAMESPACE_END(sway)
