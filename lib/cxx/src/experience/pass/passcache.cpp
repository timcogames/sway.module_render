#include <sway/render/experience/pass/passcache.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

PassCache::~PassCache() {
  for (auto &item : items_) {
    item.pass->dispose();
  }

  items_.clear();
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
