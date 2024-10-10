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
#include <vector>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class PostProcessing {
  DECLARE_CLASS_POINTER_ALIASES(PostProcessing)

public:
#pragma region "Ctors/Dtor"

  PostProcessing(gapi::ViewportPtr_t viewport);

  ~PostProcessing() = default;

#pragma endregion

  // void addPass(u32_t idx, RenderTarget::SharedPtr_t target);

  void add(RenderPass::SharedPtr_t pass, i32_t idx);

  void apply(gapi::FrameBuffer::Ptr_t framebuf);

  auto getPass(u32_t idx) -> RenderPass::SharedPtr_t;

  auto getNumPasses() const { return passes_.size(); }

  void preRender();

  void postRender();

public:
  gapi::ViewportPtr_t viewport_;
  RenderState::SharedPtr_t state_;
  std::vector<RenderPass::SharedPtr_t> passes_{};
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PPE_POSTPROCESSING_HPP
