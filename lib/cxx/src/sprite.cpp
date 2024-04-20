#include <sway/gapi.hpp>
#include <sway/render/sprite.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

#define NUM_SEGMENTS 1

void Sprite::initialize(std::shared_ptr<RenderSubsystem> subsystem, std::shared_ptr<RenderSubqueue> subqueue,
    std::shared_ptr<Material> material, const math::size2f_t &size) {
  subqueue_ = subqueue;
  material_ = material;

  std::array<gapi::VertexSemantic, 3> semantics = {
      gapi::VertexSemantic::POS, gapi::VertexSemantic::COL, gapi::VertexSemantic::TEXCOORD_0};
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
  // clang-format off
  geometry_->updateUV({
    {{
      {textureRect_.getR() / static_cast<f32_t>(texture_->getSize().getW()), textureRect_.getB() / static_cast<f32_t>(texture_->getSize().getH())},
      {textureRect_.getL() / static_cast<f32_t>(texture_->getSize().getW()), textureRect_.getB() / static_cast<f32_t>(texture_->getSize().getH())},
      {textureRect_.getR() / static_cast<f32_t>(texture_->getSize().getW()), textureRect_.getT() / static_cast<f32_t>(texture_->getSize().getH())},
      {textureRect_.getL() / static_cast<f32_t>(texture_->getSize().getW()), textureRect_.getT() / static_cast<f32_t>(texture_->getSize().getH())}
    }}
  }, math::size2i_t(NUM_SEGMENTS, NUM_SEGMENTS));
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

  geometry_->updateUV({
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
  }, math::size2i_t(NUM_SEGMENTS, NUM_SEGMENTS));
}  // clang-format on

NAMESPACE_END(render)
NAMESPACE_END(sway)
