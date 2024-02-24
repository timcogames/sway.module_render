#include <sway/gapi.hpp>
#include <sway/render/procedurals/shape.hpp>
#include <sway/render/spritebatch.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

void SpriteBatch::initialize(std::shared_ptr<RenderSubsystem> subsystem, std::shared_ptr<RenderSubqueue> subqueue,
    std::shared_ptr<Material> material, const math::size2f_t &size) {
  subqueue_ = subqueue;
  material_ = material;

  std::array<gapi::VertexSemantic, 3> semantics = {
      gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0};
  geomShape_ = std::make_shared<PlaneArray<math::VertexTexCoord>>();
  geomShape_->useVertexSemanticSet(semantics);

  geom_ = std::make_shared<Geometry>(subsystem->getIdGenerator(), material_->getEffect(), true);
  geom_->createArray(geomShape_);

  geomShape_->updateVertices(
      math::point2f_t(0.0F, 0.0F), math::size2f_t(0.5F, 0.5F), math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F));
  geomShape_->updateVertices(
      math::point2f_t(-0.6F, 0.1F), math::size2f_t(0.5F, 0.5F), math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F));
  geomShape_->updateVertices(
      math::point2f_t(0.5F, 0.5F), math::size2f_t(0.5F, 0.5F), math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F));

  gapi::BufferSubdataDescriptor subdataDesc;
  subdataDesc.offset = 0;
  subdataDesc.size = geomShape_->data_->getVtxCount();
  subdataDesc.data = geomShape_->data_->getVtxRawdata();
  auto bufset = geom_->getBufferSet();
  bufset.vbo->updateSubdata(subdataDesc);
}

void SpriteBatch::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, [[maybe_unused]] f32_t dtime) {
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
  cmd.geometry = geom_;
  cmd.material = material_;
  cmd.tfrm = tfrm;
  cmd.proj = proj;
  cmd.view = view;

  subqueue_->post(cmd);
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
