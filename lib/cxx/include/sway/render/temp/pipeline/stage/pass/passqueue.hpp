#ifndef SWAY_RENDER_PASSQUEUE_HPP
#define SWAY_RENDER_PASSQUEUE_HPP

#include <sway/core.hpp>
#include <sway/render/prereqs.hpp>
#include <sway/render/temp/pipeline/stage/pass/pass.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)

class PassQueue {
public:
  void addPass(Pass::SharedPtr_t ptr, Pass::Index_t idx = GLOB_IDX_INVALID) {
    auto pos = (idx < GLOB_IDX_INITIAL) ? passes_.end() : passes_.begin() + idx;
    passes_.insert(pos, ptr);
  }

  void apply(gapi::FrameBuffer::Ptr_t framebuf) {
    for (auto &pass : passes_) {
      pass->apply(framebuf);
    }
  }

  auto getPass(Pass::Index_t idx) -> Pass::SharedPtr_t { return passes_[idx]; }

  auto getPass(lpcstr_t name) -> Pass::SharedPtr_t {
    for (const auto &pass : passes_) {
      if (pass->name() == name) {
        return pass;
      }
    }

    return nullptr;
  }

  auto getPasses() -> Pass::SharedPtrVec_t { return passes_; }

  auto getNumOfPasses() const -> u32_t { return passes_.size(); }

private:
  Pass::SharedPtrVec_t passes_{};
};

NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_PASSQUEUE_HPP
