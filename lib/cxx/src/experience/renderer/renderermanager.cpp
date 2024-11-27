
#include <sway/render/experience/renderer/renderermanager.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

auto RendererManager::add(RendererTypedefs::UniquePtr_t renderer) -> i32_t {
  renderers_.push_back(std::move(renderer));
  return renderers_.size() - 1;
}

void RendererManager::restore(i32_t idx, RendererTypedefs::UniquePtr_t renderer) {
  if (idx == GLOB_IDX_INVALID && renderer == nullptr) {
    return;
  }

  renderers_.insert(renderers_.begin() + renderer->type(), std::move(renderer));
}

void RendererManager::erase(i32_t idx) { renderers_.erase(renderers_.begin() + idx); }

auto RendererManager::get(i32_t idx) -> RendererTypedefs::Container_t::iterator {
  return std::find_if(renderers_.begin(), renderers_.end(),
      [&](RendererTypedefs::UniquePtr_t &renderer) { return renderer != nullptr && renderer->type() == idx; });
}

auto RendererManager::size() const -> std::size_t { return renderers_.size(); }

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
