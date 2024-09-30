#include <sway/gapi.hpp>
#include <sway/render/flippable.hpp>
#include <sway/render/flipper.hpp>
#include <sway/render/procedurals/prims/quadrilateral.hpp>
#include <sway/render/procedurals/prims/quadrilateralstrip.hpp>
#include <sway/render/sprite.hpp>

#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

Sprite::~Sprite() { geomBuilder_->remove(geomIdx_); }

void Sprite::initialize(RenderSubsystem::SharedPtr_t subsys, RenderSubqueue::SharedPtr_t subqueue,
    Material::SharedPtr_t material, const math::size2f_t &size, const math::size2i_t &subdivs) {
  subqueue_ = subqueue;
  material_ = material;
  subdivs_ = subdivs;

  auto quadTempSize = size;
  auto quadHalfSize = math::size2f_t(quadTempSize / 2);

  auto quadShape = new procedurals::prims::QuadrilateralStrip<math::VertexTexCoord>(
      {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0}, subdivs_);

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
  geomCreateInfo.bo[Constants::IDX_VBO].desc.capacity = quadShape->getReserveVerts();
  auto data = new f32_t[quadShape->getReserveVerts() * sizeof(math::VertexTexCoord)];
  quadShape->data()->getVertices(data, 0, quadShape->getReserveVerts());
  geomCreateInfo.bo[Constants::IDX_VBO].data = data;

  geomCreateInfo.bo[Constants::IDX_EBO].desc.usage = gapi::BufferUsage::STATIC;
  geomCreateInfo.bo[Constants::IDX_EBO].desc.byteStride = sizeof(u32_t);
  geomCreateInfo.bo[Constants::IDX_EBO].desc.capacity = quadShape->getReserveElems();
  geomCreateInfo.bo[Constants::IDX_EBO].data = quadShape->data()->getElements();

  geomBuilder_ = subsys->getGeomBuilder();

  geomIdx_ = geomBuilder_->create<procedurals::prims::QuadrilateralStrip<math::VertexTexCoord>>(
      geomCreateInfo, quadShape->getVertexAttribs(), material_->getEffect());

  this->setTexture(material_->getImage(0 /* ALBEDO */), false);
}

void Sprite::onUpdate(math::mat4f_t tfrm, math::mat4f_t proj, math::mat4f_t view, [[maybe_unused]] f32_t dtm) {
  auto geom = geomBuilder_->getGeometry(geomIdx_);
  if (!geom) {
    return;
  }

  pipeline::ForwardRenderCommand cmd;
  cmd.stage = core::detail::toBase(RenderStage::IDX_COLOR);
  cmd.blendDesc.enabled = true;
  cmd.blendDesc.src = gapi::BlendFn::SRC_ALPHA;
  cmd.blendDesc.dst = gapi::BlendFn::ONE_MINUS_SRC_ALPHA;
  cmd.blendDesc.mask = true;
  cmd.rasterizerDesc.mode = gapi::CullFace::FRONT;
  cmd.rasterizerDesc.ccw = true;
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
  cmd.mtrl = material_;
  cmd.tfrm = tfrm;
  cmd.proj = proj;
  cmd.view = view;
  subqueue_->post(cmd);
}

void Sprite::setTexture(Image::SharedPtr_t texture, bool recomputeUVRequired) {
  if (recomputeUVRequired) {
    setTextureRect(math::rect4i_t(0, 0, texture->getSize()));
  }

  texture_ = texture;
}

auto Sprite::getTexture() const -> Image::SharedPtr_t { return texture_; }

void Sprite::setTextureRect(const math::rect4i_t &rect) {
  if (textureRect_.equals(rect)) {
    return;
  }

  textureRect_ = rect;
  recomputeUV();
}

auto Sprite::getTextureRect() const -> math::rect4i_t { return textureRect_; }

auto recomputeUVWithBorder(
    const math::vec2f_t &pos, const math::sizef_t &size, const math::size2i_t &subdivs) -> std::vector<UVData2> {
  std::vector<UVData2> out;
  std::vector<math::vec2f_t> uv;
  auto texIdx = 0;

  for (auto y = 0; y < subdivs.getH() + 1; y++) {
    for (auto x = 0; x < subdivs.getW() + 1; x++) {
      auto data = math::vec2f_t(pos.getX() + size.getW() * x, pos.getY() + size.getH() * y);
      uv.push_back(data);
      texIdx += 1;

      if (texIdx >= QUAD_TEXCOORD_SIZE2) {
        out.push_back({uv});
        uv.clear();
        texIdx = 0;
      }
    }
  }

  return out;
}

void Sprite::recomputeUV() {
  auto textureSize = texture_->getSize();

  if (subdivs_.area() > 1) {
    // clang-format off
    auto pos = math::vec2f_t(
       textureRect_.getL() / static_cast<f32_t>(textureSize.getW()),
       textureRect_.getT() / static_cast<f32_t>(textureSize.getH())
    );

    auto chunkSize = math::sizef_t(
      (textureRect_.getW() / static_cast<f32_t>(textureSize.getW())) / subdivs_.getW(),
      (textureRect_.getH() / static_cast<f32_t>(textureSize.getH())) / subdivs_.getH()
    );

    geomBuilder_->getGeometry(geomIdx_)->updateUV(recomputeUVWithBorder(pos, chunkSize, subdivs_));
    // clang-format on
  } else {
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
