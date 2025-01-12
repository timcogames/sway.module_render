
#include <sway/render/experience/renderer/renderermanager.hpp>

namespace sway::render {
NS_BEGIN(experience)

auto RendererManager::add(RendererTypedefs::UniquePtr_t renderer) -> i32_t {
  renderers_.emplace_back(std::move(renderer));
  return static_cast<i32_t>(renderers_.size() - 1);
}

void RendererManager::restore(i32_t idx, RendererTypedefs::UniquePtr_t renderer) {
  if (idx == GLOB_IDX_INVALID && renderer == nullptr) {
    return;
  }

  renderers_.insert(renderers_.begin() + renderer->getType(), std::move(renderer));
}

void RendererManager::erase(i32_t idx) { renderers_.erase(renderers_.begin() + idx); }

auto RendererManager::find(i32_t type) -> RendererTypedefs::Container_t::iterator {
  // clang-format off
  return std::find_if(renderers_.begin(), renderers_.end(), 
    [type](const auto &renderer) {
      return renderer && renderer->getType() == type;
    });
  // clang-format on
}

auto RendererManager::getSize() const -> std::size_t { return renderers_.size(); }

NS_END()  // namespace experience
}  // namespace sway::render
