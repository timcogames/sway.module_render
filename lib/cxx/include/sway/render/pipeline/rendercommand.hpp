#ifndef SWAY_RENDER_PIPELINE_RENDERCOMMAND_HPP
#define SWAY_RENDER_PIPELINE_RENDERCOMMAND_HPP

#include <sway/core.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/effect/effect.hpp>
#include <sway/render/geom/_typedefs.hpp>
#include <sway/render/geom/geom.hpp>
#include <sway/render/img/image.hpp>
#include <sway/render/mtrl/_typedefs.hpp>
#include <sway/render/pipeline/blenddescriptor.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

#include <memory>
#include <string>
#include <vector>

namespace sway::render {
NS_BEGIN(pipeline)

struct RenderCommand {};

// struct ForwardRenderPass {
//   StencilStateData stencil;
//   DepthStateData depth;
//   std::shared_ptr<Geometry> geometry;
//   std::shared_ptr<Material> material;
// };

struct ForwardRenderCommand : public RenderCommand {
  i32_t index;
  u32_t stage;
  i32_t zorder{0};

  BlendDescriptor blendDesc;
  // std::array<ForwardRenderPass, 4> passes{};

  gapi::RasterizerDescriptor rasterizerDesc;
  gapi::DepthDescriptor depthDesc;
  gapi::StencilDescriptor stencilDesc;

  GeomTypedefs::Ptr_t geom;
  gapi::TopologyType::Enum topology;
  MaterialTypedefs::SharedPtr_t mtrl;

  math::mat4f_t tfrm;
  math::mat4f_t proj;
  math::mat4f_t view;

  ForwardRenderCommand()
      : geom(nullptr) {}
};

struct CameraRenderCommand : public RenderCommand {
  i32_t viewport;
  math::mat4f_t proj;
  math::mat4f_t view;
  math::vec3f_t eye;
  math::vec3f_t pos;
  i32_t order;
  i32_t mask;
  f32_t near;
  f32_t far;
};

NS_END()  // namespace pipeline
}  // namespace sway::render

#endif  // SWAY_RENDER_PIPELINE_RENDERCOMMAND_HPP
