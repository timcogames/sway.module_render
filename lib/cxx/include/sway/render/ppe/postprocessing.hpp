#ifndef SWAY_RENDER_PPE_POSTPROCESSING_HPP
#define SWAY_RENDER_PPE_POSTPROCESSING_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/render/_stdafx.hpp>
#include <sway/render/ppe/postprocessingpass.hpp>
#include <sway/render/renderstate.hpp>
#include <sway/render/rendertarget.hpp>

#include <array>
#include <vector>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class PostProcessing {
public:
#pragma region "Ctors/Dtor"

  PostProcessing(gapi::typedefs::ViewportPtr_t viewport);

  ~PostProcessing() = default;

#pragma endregion

  // void addPass(u32_t idx, typedefs::RenderTargetSharedPtr_t target);

  void add(std::shared_ptr<PostProcessingPass> pass, i32_t idx);

  void apply(gapi::typedefs::FrameBufferPtr_t framebuf);

  auto getPass(u32_t idx) -> std::shared_ptr<PostProcessingPass>;

  auto getNumPasses() const { return passes_.size(); }

  void preRender();

  void postRender();

public:
  gapi::typedefs::ViewportPtr_t viewport_;
  typedefs::RenderStateSharedPtr_t state_;
  std::vector<std::shared_ptr<PostProcessingPass>> passes_{};
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PPE_POSTPROCESSING_HPP
