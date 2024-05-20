#include <sway/gapi.hpp>
#include <sway/render/flippable.hpp>
#include <sway/render/flipper.hpp>
#include <sway/render/procedurals/prims/quadrilateral.hpp>
#include <sway/render/procedurals/prims/quadrilateralstrip.hpp>
#include <sway/render/sprite.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Sprite::~Sprite() { geomBuilder_->remove(geomIdx_); }

void Sprite::initialize(std::shared_ptr<RenderSubsystem> subsystem, std::shared_ptr<RenderSubqueue> subqueue,
    std::shared_ptr<Material> material, const math::size2f_t &size = math::size2f_one) {
  subqueue_ = subqueue;
  material_ = material;

  auto quadTempSize = size;
  auto quadHalfSize = math::size2f_t(quadTempSize / 2);

  auto quadShape = new procedurals::prims::QuadrilateralStrip<math::VertexTexCoord>(
      {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0});

  core::detail::EnumClassBitset<Flipper> flips;
  // flips.set(Flipper::HORZ);
  // flips.set(Flipper::VERT);

  quadShape->setPosDataAttrib(Flippable::asRect(
      math::rect4f_t(0, 0, size.getW(), size.getH()).offset(-quadHalfSize.getW(), -quadHalfSize.getH()), flips));
  quadShape->setColDataAttrib(COL4F_WHITE);
  quadShape->setTexDataAttrib(math::rect4f_t(0.0F, 0.0F, 1.0F, 1.0F));

  GeometryCreateInfo geomCreateInfo;
  geomCreateInfo.indexed = true;
  geomCreateInfo.topology = gapi::TopologyType::TRIANGLE_STRIP;
  geomCreateInfo.bo[Constants::IDX_VBO].desc.usage = gapi::BufferUsage::STATIC;
  geomCreateInfo.bo[Constants::IDX_VBO].desc.byteStride = sizeof(math::VertexTexCoord);
  geomCreateInfo.bo[Constants::IDX_VBO].desc.capacity =
      procedurals::prims::QuadrilateralStrip<math::VertexTexCoord>::MAX_QUAD_RESERVE_VERTICES;
  auto data = new f32_t[procedurals::prims::QuadrilateralStrip<math::VertexTexCoord>::MAX_QUAD_RESERVE_VERTICES *
                        sizeof(math::VertexTexCoord)];
  quadShape->data()->getVertices(
      data, 0, procedurals::prims::QuadrilateralStrip<math::VertexTexCoord>::MAX_QUAD_RESERVE_VERTICES);
  geomCreateInfo.bo[Constants::IDX_VBO].data = data;

  geomCreateInfo.bo[Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
  geomCreateInfo.bo[Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
  geomCreateInfo.bo[Constants::IDX_EBO].desc.capacity =
      procedurals::prims::QuadrilateralStrip<math::VertexTexCoord>::MAX_QUAD_RESERVE_ELEMENTS;
  geomCreateInfo.bo[Constants::IDX_EBO].data = quadShape->data()->getElements();

  geomBuilder_ = subsystem->getGeomBuilder();

  geomIdx_ = geomBuilder_->create<procedurals::prims::QuadrilateralStrip<math::VertexTexCoord>>(
      geomCreateInfo, quadShape->getVertexAttribs(), material_->getEffect());

  this->setTexture(material_->getImage(0 /* ALBEDO */), false);
}

void Sprite::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, [[maybe_unused]] f32_t dtime) {
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
  cmd.topology = gapi::TopologyType::TRIANGLE_STRIP;
  cmd.material = material_;
  cmd.tfrm = tfrm;
  cmd.proj = proj;
  cmd.view = view;
  subqueue_->post(cmd);
}

void Sprite::setTexture(Image::Ptr texture, bool recomputeUVRequired) {
  if (recomputeUVRequired) {
    setTextureRect(math::rect4i_t(0, 0, texture->getSize()));
  }

  texture_ = texture;
}

auto Sprite::getTexture() const -> Image::Ptr { return texture_; }

void Sprite::setTextureRect(const math::rect4i_t &rect) {
  if (textureRect_.equals(rect)) {
    return;
  }

  textureRect_ = rect;
  recomputeUV();
}

auto Sprite::getTextureRect() const -> math::rect4i_t { return textureRect_; }

void Sprite::recomputeUV() {
  auto textureSize = texture_->getSize();

  // clang-format off
  geomBuilder_->getGeometry(geomIdx_)->updateUV({
    {{
      {textureRect_.getL() / static_cast<f32_t>(textureSize.getW()), textureRect_.getT() / static_cast<f32_t>(textureSize.getH())},
      {textureRect_.getR() / static_cast<f32_t>(textureSize.getW()), textureRect_.getT() / static_cast<f32_t>(textureSize.getH())},
      {textureRect_.getL() / static_cast<f32_t>(textureSize.getW()), textureRect_.getB() / static_cast<f32_t>(textureSize.getH())},
      {textureRect_.getR() / static_cast<f32_t>(textureSize.getW()), textureRect_.getB() / static_cast<f32_t>(textureSize.getH())}
    }}
  });
  // clang-format on
}

// clang-format off
void Sprite::updateGeometryUV(math::size2i_t textureSize, math::rect4f_t frameRect) {
  // geometry_->setUV(std::array<TexCoord, 4> {{
  //   {frameRect.getR() / static_cast<f32_t>(textureSize.getW()), frameRect.getB() / static_cast<f32_t>(textureSize.getH())},
  //   {frameRect.getL() / static_cast<f32_t>(textureSize.getW()), frameRect.getB() / static_cast<f32_t>(textureSize.getH())},
  //   {frameRect.getR() / static_cast<f32_t>(textureSize.getW()), frameRect.getT() / static_cast<f32_t>(textureSize.getH())},
  //   {frameRect.getL() / static_cast<f32_t>(textureSize.getW()), frameRect.getT() / static_cast<f32_t>(textureSize.getH())}
  // }}.data());

  geomBuilder_->getGeometry(geomIdx_)->updateUV({
    {{
      {frameRect.getR() / static_cast<f32_t>(textureSize.getW()), frameRect.getB() / static_cast<f32_t>(textureSize.getH())},
      {frameRect.getL() / static_cast<f32_t>(textureSize.getW()), frameRect.getB() / static_cast<f32_t>(textureSize.getH())},
      {frameRect.getR() / static_cast<f32_t>(textureSize.getW()), frameRect.getT() / static_cast<f32_t>(textureSize.getH())},
      {frameRect.getL() / static_cast<f32_t>(textureSize.getW()), frameRect.getT() / static_cast<f32_t>(textureSize.getH())}
    }},

    // {{
    //   {frameRect.getR() / static_cast<f32_t>(textureSize.getW()), frameRect.getB() / static_cast<f32_t>(textureSize.getH())},
    //   {frameRect.getL() / static_cast<f32_t>(textureSize.getW()), frameRect.getB() / static_cast<f32_t>(textureSize.getH())},
    //   {frameRect.getR() / static_cast<f32_t>(textureSize.getW()), frameRect.getT() / static_cast<f32_t>(textureSize.getH())},
    //   {frameRect.getL() / static_cast<f32_t>(textureSize.getW()), frameRect.getT() / static_cast<f32_t>(textureSize.getH())}
    // }},

    // {{
    //   {frameRect.getR() / static_cast<f32_t>(textureSize.getW()), frameRect.getB() / static_cast<f32_t>(textureSize.getH())},
    //   {frameRect.getL() / static_cast<f32_t>(textureSize.getW()), frameRect.getB() / static_cast<f32_t>(textureSize.getH())},
    //   {frameRect.getR() / static_cast<f32_t>(textureSize.getW()), frameRect.getT() / static_cast<f32_t>(textureSize.getH())},
    //   {frameRect.getL() / static_cast<f32_t>(textureSize.getW()), frameRect.getT() / static_cast<f32_t>(textureSize.getH())}
    // }},

    // {{
    //   {frameRect.getR() / static_cast<f32_t>(textureSize.getW()), frameRect.getB() / static_cast<f32_t>(textureSize.getH())},
    //   {frameRect.getL() / static_cast<f32_t>(textureSize.getW()), frameRect.getB() / static_cast<f32_t>(textureSize.getH())},
    //   {frameRect.getR() / static_cast<f32_t>(textureSize.getW()), frameRect.getT() / static_cast<f32_t>(textureSize.getH())},
    //   {frameRect.getL() / static_cast<f32_t>(textureSize.getW()), frameRect.getT() / static_cast<f32_t>(textureSize.getH())}
    // }}
  });
}  // clang-format on

NAMESPACE_END(render)
NAMESPACE_END(sway)
