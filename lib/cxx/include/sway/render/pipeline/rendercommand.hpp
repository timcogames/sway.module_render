#ifndef SWAY_RENDER_PIPELINE_RENDERCOMMAND_HPP
#define SWAY_RENDER_PIPELINE_RENDERCOMMAND_HPP

#include <sway/core.hpp>
#include <sway/render/effect.hpp>
#include <sway/render/geom/geom.hpp>
#include <sway/render/geometry.hpp>
#include <sway/render/image.hpp>
#include <sway/render/material.hpp>
#include <sway/render/pipeline/blenddescriptor.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/rendersubqueuegroups.hpp>

#include <memory>
#include <string>
#include <vector>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)
NAMESPACE_BEGIN(pipeline)

struct RenderCommand {};

// struct ForwardRenderPass {
//   StencilStateData stencil;
//   DepthStateData depth;
//   std::shared_ptr<Geometry> geometry;
//   std::shared_ptr<Material> material;
// };

struct ForwardRenderCommand : public RenderCommand {
  u32_t stage;

  BlendDescriptor blendDesc;
  // std::array<ForwardRenderPass, 4> passes{};

  gapi::RasterizerDescriptor rasterizerDesc;
  gapi::DepthDescriptor depthDesc;
  gapi::StencilDescriptor stencilDesc;

  std::shared_ptr<Geometry> geometry;
  Geom *geom;
  gapi::TopologyType topology;
  Material::SharedPtr_t material;

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

NAMESPACE_END(pipeline)
NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PIPELINE_RENDERCOMMAND_HPP
