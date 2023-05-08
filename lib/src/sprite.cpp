#include <sway/render/sprite.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

void Sprite::initialize(std::shared_ptr<RenderSubsystem> subsystem, std::shared_ptr<RenderSubqueue> subqueue,
    std::shared_ptr<Material> material, const math::size2f_t &size, const math::col4f_t &col) {
  subqueue_ = subqueue;
  material_ = material;

  std::array<gapi::VertexSemantic, 2> semantics = {gapi::VertexSemantic::POS, gapi::VertexSemantic::TEXCOORD_0};
  auto plane = std::make_shared<procedurals::prims::Plane<math::VertexTexCoord>>(size, col);
  plane->useVertexSemanticSet(semantics);

  geometry_ = std::make_shared<Geometry>(subsystem->getIdGenerator(), material_->getEffect(), true);
  geometry_->create(plane);
}

void Sprite::onUpdate(math::mat4f_t transform, math::mat4f_t proj, f32_t deltaTime) {
  pipeline::ForwardRenderCommand command;
  command.geometry = geometry_;
  command.effect = material_->getEffect();
  command.images = material_->getImages();
  command.transform = transform;
  command.proj = proj;

  subqueue_->post(command);
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
