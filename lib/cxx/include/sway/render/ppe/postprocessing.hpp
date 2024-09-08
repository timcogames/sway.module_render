#ifndef SWAY_RENDER_PPE_POSTPROCESSING_HPP
#define SWAY_RENDER_PPE_POSTPROCESSING_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderpass.hpp>
#include <sway/render/renderstages.hpp>
#include <sway/render/renderstate.hpp>
#include <sway/render/rendertarget.hpp>

#include <array>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(render)

class PostProcessing {
  DECLARE_CLASS_POINTER_ALIASES(PostProcessing)

public:
#pragma region "Ctors/Dtor"

  PostProcessing(gapi::ViewportPtr_t viewport);

  ~PostProcessing() = default;

#pragma endregion

  void addPass(u32_t idx);

  void preRender();

  void postRender();

public:
  RenderTarget::SharedPtr_t target_;
  RenderState::SharedPtr_t state_;
  std::array<RenderPass::SharedPtr_t, MAX_RENDER_STAGES> passes_{};
};

NAMESPACE_END(render)
NAMESPACE_END(sway)

#endif  // SWAY_RENDER_PPE_POSTPROCESSING_HPP
