#include <sway/render/procedurals/guides/axis.hpp>
#include <sway/render/procedurals/prims/plane_debug.hpp>
#include <sway/render/sprite_debug.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

#define NUM_SEGMENTS 4

struct VertexColor2 {
  f32_t x, y, z;
  f32_t r, g, b;
};

void Sprite_Debug::initialize(std::shared_ptr<RenderSubsystem> subsystem, std::shared_ptr<RenderSubqueue> subqueue,
    std::shared_ptr<Material> material, const math::size2f_t &size) {
  subqueue_ = subqueue;
  material_ = material;

  std::array<gapi::VertexSemantic, 2> semantics = {gapi::VertexSemantic::POS, gapi::VertexSemantic::COL};
  auto plane =
      std::make_shared<procedurals::prims::Plane_Debug<VertexColor2>>(size, math::size2i_t(NUM_SEGMENTS, NUM_SEGMENTS));
  // auto plane = std::make_shared<procedurals::guides::Axis<math::VertexColor>>(size);
  plane->useVertexSemanticSet(semantics);

  geometry_ = std::make_shared<Geometry>(subsystem->getIdGenerator(), material_->getEffect(), false);
  geometry_->create(plane);
}

void Sprite_Debug::onUpdate(
    math::mat4f_t transform, math::mat4f_t proj, math::mat4f_t view, [[maybe_unused]] f32_t deltaTime) {
  pipeline::ForwardRenderCommand cmd;
  cmd.geometry = geometry_;
  cmd.effect = material_->getEffect();
  cmd.images = material_->getImages();
  cmd.transform = transform;
  cmd.proj = proj;
  cmd.view = view;

  subqueue_->post(cmd);
}

NAMESPACE_END(render)
NAMESPACE_END(sway)
