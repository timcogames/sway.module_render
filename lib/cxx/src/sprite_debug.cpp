#include <sway/render/procedurals/guides/axis.hpp>
#include <sway/render/procedurals/guides/line.hpp>
#include <sway/render/sprite_debug.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

void Sprite_Debug::initialize(std::shared_ptr<RenderSubsystem> subsystem, std::shared_ptr<RenderSubqueue> subqueue,
    std::shared_ptr<Material> material) {
  subqueue_ = subqueue;
  material_ = material;

  auto axisLineShape =
      new procedurals::guides::Line<math::VertexColor>({gapi::VertexSemantic::POS, gapi::VertexSemantic::COL});

  axisLineShape->setPosDataAttrib(math::vec3f_zero, math::vec3f_t(1.0F, 1.0F, 0.0F));
  axisLineShape->setColDataAttrib(COL4F_WHITE);

  GeometryCreateInfo geomCreateInfo;
  geomCreateInfo.indexed = false;
  geomCreateInfo.topology = gapi::TopologyType::LINE_LIST;
  geomCreateInfo.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::STATIC;
  geomCreateInfo.bo[Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexColor);
  geomCreateInfo.bo[Constants::IDX_VBO].desc.capacity = 2;
  auto data = new f32_t[2 * sizeof(math::VertexColor)];
  axisLineShape->data()->getVertices(data, 0, 2);
  geomCreateInfo.bo[Constants::IDX_VBO].data = data;

  geomBuilder_ = subsystem->getGeomBuilder();

  geomIdx_ = geomBuilder_->create<procedurals::guides::Line<math::VertexColor>>(
      geomCreateInfo, axisLineShape->getVertexAttribs(), material_->getEffect());
}

void Sprite_Debug::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, [[maybe_unused]] f32_t dtime) {
  auto geom = geomBuilder_->getGeometry(geomIdx_);
  if (!geom) {
    return;
  }

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
  cmd.geom = geom;
  cmd.topology = gapi::TopologyType::LINE_LIST;
  cmd.material = material_;
  cmd.tfrm = tfrm;
  cmd.proj = proj;
  cmd.view = view;
  subqueue_->post(cmd);
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
