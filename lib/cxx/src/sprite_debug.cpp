#include <sway/render/procedurals/guides/axis.hpp>
#include <sway/render/procedurals/guides/line.hpp>
#include <sway/render/sprite_debug.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

Sprite_Debug::~Sprite_Debug() {
  geomBuilder_->remove(axisGeomIdx_);
  //  geomBuilder_->remove(lineGeomIdx_);
}

void Sprite_Debug::initialize(
    RenderSubsystem::SharedPtr_t subsystem, RenderSubqueue::SharedPtr_t subqueue, Material::SharedPtr_t material) {
  geomBuilder_ = subsystem->getGeomBuilder();

  subqueue_ = subqueue;
  material_ = material;

  // auto lineShape = new procedurals::guides::Line();

  // lineShape->setPosDataAttrib(math::vec3f_zero, math::vec3f_t(1.0F, 1.0F, 0.0F));
  // lineShape->setColDataAttrib(COL4F_WHITE);

  // GeometryCreateInfo lineGeomCreateInfo;
  // lineGeomCreateInfo.indexed = false;
  // lineGeomCreateInfo.topology = gapi::TopologyType::LINE_LIST;
  // lineGeomCreateInfo.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::STATIC;
  // lineGeomCreateInfo.bo[Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexColor);
  // lineGeomCreateInfo.bo[Constants::IDX_VBO].desc.capacity = procedurals::guides::Line::MAX_LINE_RESERVE_VERTICES;
  // auto lineShapeVtxData = new f32_t[procedurals::guides::Line::MAX_LINE_RESERVE_VERTICES *
  // sizeof(math::VertexColor)]; lineShape->data()->getVertices(lineShapeVtxData, 0,
  // procedurals::guides::Line::MAX_LINE_RESERVE_VERTICES); lineGeomCreateInfo.bo[Constants::IDX_VBO].data =
  // lineShapeVtxData; lineGeomIdx_ = geomBuilder_->create<procedurals::guides::Line>(
  //     lineGeomCreateInfo, lineShape->getVertexAttribs(), material_->getEffect());

  auto axisShape = new procedurals::guides::Axis();

  GeometryCreateInfo axisGeomCreateInfo;
  axisGeomCreateInfo.indexed = true;
  axisGeomCreateInfo.topology = gapi::TopologyType::Enum::LINE_LIST;
  axisGeomCreateInfo.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::Enum::STATIC;
  axisGeomCreateInfo.bo[Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexColor);
  axisGeomCreateInfo.bo[Constants::IDX_VBO].desc.capacity = procedurals::guides::Axis::MAX_AXIS_RESERVE_VERTICES;
  auto axisShapeVtxData = new f32_t[procedurals::guides::Axis::MAX_AXIS_RESERVE_VERTICES * sizeof(math::VertexColor)];
  axisShape->data()->getVertices(axisShapeVtxData, 0, procedurals::guides::Axis::MAX_AXIS_RESERVE_VERTICES);
  axisGeomCreateInfo.bo[Constants::IDX_VBO].data = axisShapeVtxData;

  axisGeomCreateInfo.bo[Constants::IDX_EBO].desc.usage = gapi::BufferUsage::Enum::STATIC;
  axisGeomCreateInfo.bo[Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
  axisGeomCreateInfo.bo[Constants::IDX_EBO].desc.capacity = procedurals::guides::Axis::MAX_AXIS_RESERVE_ELEMENTS;
  axisGeomCreateInfo.bo[Constants::IDX_EBO].data = axisShape->data()->getElements();
  axisGeomIdx_ = geomBuilder_->create<procedurals::guides::Axis>(
      axisGeomCreateInfo, axisShape->getVertexAttribs(), material_->getEffect());
}

void Sprite_Debug::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, [[maybe_unused]] f32_t dtm) {
  // auto lineGeom = geomBuilder_->getGeometry(lineGeomIdx_);
  // if (!lineGeom) {
  //   return;
  // }

  // pipeline::ForwardRenderCommand lineCmd;
  // lineCmd.stage = 0;
  // lineCmd.blendDesc.enabled = true;
  // lineCmd.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
  // lineCmd.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
  // lineCmd.blendDesc.mask = true;
  // lineCmd.rasterizerDesc.mode = gapi::CullFace::BACK;
  // lineCmd.rasterizerDesc.ccw = false;
  // lineCmd.depthDesc.enabled = true;
  // lineCmd.depthDesc.func = gapi::CompareFn::LESS;
  // lineCmd.depthDesc.mask = true;
  // lineCmd.depthDesc.near = 0;
  // lineCmd.depthDesc.far = 0;
  // lineCmd.stencilDesc.enabled = true;
  // lineCmd.stencilDesc.front.func = gapi::CompareFn::ALWAYS;
  // lineCmd.stencilDesc.front.fail = gapi::StencilOp::KEEP;
  // lineCmd.stencilDesc.front.depthFail = gapi::StencilOp::KEEP;
  // lineCmd.stencilDesc.front.depthPass = gapi::StencilOp::REPLACE;
  // lineCmd.stencilDesc.front.rmask = 0xFFFFFF;
  // lineCmd.stencilDesc.front.wmask = lineCmd.stencilDesc.front.rmask;
  // lineCmd.stencilDesc.front.reference = 1;
  // lineCmd.stencilDesc.back = lineCmd.stencilDesc.front;
  // lineCmd.geom = lineGeom;
  // lineCmd.topology = gapi::TopologyType::LINE_LIST;
  // lineCmd.material = material_;
  // lineCmd.tfrm = tfrm;
  // lineCmd.proj = proj;
  // lineCmd.view = view;
  // subqueue_->post(lineCmd);

  auto axisGeom = geomBuilder_->getGeometry(axisGeomIdx_);
  if (!axisGeom) {
    return;
  }

  pipeline::ForwardRenderCommand axisCmd;
  axisCmd.stage = core::detail::toBase(RenderStage::IDX_COLOR);
  axisCmd.blendDesc.enabled = false;
  axisCmd.blendDesc.src = gapi::BlendFn::Enum::SRC_ALPHA;
  axisCmd.blendDesc.dst = gapi::BlendFn::Enum::ONE_MINUS_SRC_ALPHA;
  axisCmd.blendDesc.mask = false;
  // axisCmd.rasterizerDesc.mode = gapi::CullFace::BACK;
  // axisCmd.rasterizerDesc.ccw = false;
  axisCmd.depthDesc.enabled = false;
  axisCmd.depthDesc.func = gapi::CompareFn::Enum::LESS;
  // axisCmd.depthDesc.mask = true;
  // axisCmd.depthDesc.near = 0;
  // axisCmd.depthDesc.far = 0;
  axisCmd.stencilDesc.enabled = false;
  axisCmd.stencilDesc.front.func = gapi::CompareFn::Enum::ALWAYS;
  axisCmd.stencilDesc.front.fail = gapi::StencilOp::Enum::KEEP;
  axisCmd.stencilDesc.front.depthFail = gapi::StencilOp::Enum::KEEP;
  axisCmd.stencilDesc.front.depthPass = gapi::StencilOp::Enum::REPLACE;
  axisCmd.stencilDesc.front.rmask = 0xFFFFFF;
  axisCmd.stencilDesc.front.wmask = axisCmd.stencilDesc.front.rmask;
  axisCmd.stencilDesc.front.reference = 1;
  axisCmd.stencilDesc.back = axisCmd.stencilDesc.front;
  axisCmd.geom = axisGeom;
  axisCmd.topology = gapi::TopologyType::Enum::LINE_LIST;
  axisCmd.mtrl = material_;
  axisCmd.tfrm = tfrm;
  axisCmd.proj = proj;
  axisCmd.view = view;
  subqueue_->post(axisCmd);
}

NS_END()  // namespace render
NS_END()  // namespace sway
