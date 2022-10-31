#include <sway/graphics/primitives/quad.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(graphics)
NAMESPACE_BEGIN(primitives)

Quad::Quad(f32_t width, f32_t height)
    : VertexData(4) {
  auto halfSize = math::TSize<f32_t>(width, height);

  auto positionChannel = createChannel<math::vec3f_t>(gapi::VertexSemantic_t::kPosition, 8);
  auto positionChannelCapacity = 0;
  positionChannel->addAnyData(math::vec3f_t(-halfSize.getW(), +halfSize.getH(), 0.0).data(), positionChannelCapacity);
  positionChannel->addAnyData(math::vec3f_t(-halfSize.getW(), -halfSize.getH(), 0.0).data(), positionChannelCapacity);
  positionChannel->addAnyData(math::vec3f_t(+halfSize.getW(), +halfSize.getH(), 0.0).data(), positionChannelCapacity);
  positionChannel->addAnyData(math::vec3f_t(+halfSize.getW(), -halfSize.getH(), 0.0).data(), positionChannelCapacity);

  auto colorChannel = createChannel<math::vec4f_t>(gapi::VertexSemantic_t::kColor, 8);
  auto colorChannelCapacity = 0;
  colorChannel->addAnyData(math::vec4f_t(1.0, 1.0, 1.0, 1.0).data(), colorChannelCapacity);
  colorChannel->addAnyData(math::vec4f_t(1.0, 1.0, 1.0, 1.0).data(), colorChannelCapacity);
  colorChannel->addAnyData(math::vec4f_t(1.0, 1.0, 1.0, 1.0).data(), colorChannelCapacity);
  colorChannel->addAnyData(math::vec4f_t(1.0, 1.0, 1.0, 1.0).data(), colorChannelCapacity);

  addTriIndices(0, 1, 2);
  addTriIndices(1, 3, 2);
}

NAMESPACE_END(primitives)
NAMESPACE_END(graphics)
NAMESPACE_END(sway)
