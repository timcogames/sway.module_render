#ifndef SWAY_RENDER_RENDERPASSMANAGER_HPP
#define SWAY_RENDER_RENDERPASSMANAGER_HPP

#include <sway/core.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/renderpass.hpp>

#include <vector>  // std::vector

NS_BEGIN_SWAY()
NS_BEGIN(render)

class RenderPassManager {
  DECLARE_CLASS_POINTER_ALIASES(RenderPassManager)

public:
  void addPass(RenderPass::SharedPtr_t pass, i32_t idx) {
    if (idx < 0) {
      passes_.push_back(pass);
    } else {
      passes_.insert(passes_.begin() + idx, pass);
    }
  }

  void apply(gapi::FrameBuffer::Ptr_t framebuf) {
    for (auto &pass : passes_) {
      pass->apply(framebuf);
    }
  }

  auto getPass(u32_t idx) -> RenderPass::SharedPtr_t { return passes_[idx]; }

  auto getPass(lpcstr_t name) -> RenderPass::SharedPtr_t {
    for (const auto &pass : passes_) {
      if (pass->name() == name) {
        return pass;
      }
    }

    return nullptr;
  }

  auto getNumPasses() const { return passes_.size(); }

private:
  RenderPass::SharedPtrVec_t passes_{};
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_RENDERPASSMANAGER_HPP
