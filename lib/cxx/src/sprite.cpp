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
  cmd.blendDesc.enabled = true;
  cmd.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
  cmd.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
  cmd.blendDesc.mask = true;
  cmd.rasterizerDesc.mode = gapi::CullFace::BACK;
  cmd.rasterizerDesc.ccw = false;
  cmd.depthDesc.enabled = true;
  cmd.depthDesc.func = gapi::CompareFn::LESS;
  cmd.depthDesc.mask = true;
  cmd.depthDesc.near = 0;
  cmd.depthDesc.far = 0;
  cmd.stencilDesc.enabled = true;
  cmd.stencilDesc.front.func = gapi::CompareFn::ALWAYS;
  cmd.stencilDesc.front.fail = gapi::StencilOp::KEEP;
  cmd.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
  cmd.stencilDesc.front.depthPass = gapi::StencilOp::REPLACE;
  cmd.stencilDesc.front.rmask = 0xFFFFFF;
  cmd.stencilDesc.front.wmask = cmd.stencilDesc.front.rmask;
  cmd.stencilDesc.front.reference = 1;
  cmd.stencilDesc.back = cmd.stencilDesc.front;
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
