#ifndef SWAY_RENDER_RENDERER_HPP
#define SWAY_RENDER_RENDERER_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/temp/pipeline.hpp>
#include <sway/render/temp/renderertypes.hpp>

#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class Renderer {
  DECLARE_PTR_ALIASES(Renderer)
  DECLARE_PTR_VECTOR(Renderer, SharedPtr)

public:
#pragma region "Ctors/Dtor"

  Renderer(RendererType::Enum type)
      : type_(type) {
    pipeline_ = new Pipeline();
  }

  DTOR_VIRTUAL(Renderer) { SAFE_DELETE_OBJECT(pipeline_); }

#pragma endregion

  auto getPipeline() -> Pipeline::Ptr_t { return pipeline_; }

  auto type() const -> RendererType::Enum { return type_; }

private:
  Pipeline::Ptr_t pipeline_;
  RendererType::Enum type_;
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERER_HPP
