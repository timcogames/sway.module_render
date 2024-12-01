#include <sway/render/experience/pass/passdescriptor.hpp>
#include <sway/render/experience/utility/cache.hpp>
#include <sway/render/experience/utility/cacheable.hpp>

namespace std {
template <>
struct hash<sway::render::experience::PassDescriptor> {
  auto operator()(const sway::render::experience::PassDescriptor &desc) const noexcept -> size_t {
    return desc.hashValue();
  }
};
}  // namespace std

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

template <typename TYPE, typename DESC>
auto Cache::getOrCreate(const DESC &desc) -> TYPE * {
  auto hash = core::misc::hashValue(desc);
  auto iter = std::find_if(items_.begin(), items_.end(), [hash](const auto &item) { return item.hash == hash; });
  if (iter != items_.end()) {
    return static_cast<TYPE *>(iter->data.get());
  }

  items_.emplace_back(CacheItem{hash, std::make_unique<TYPE>(desc)});
  return static_cast<TYPE *>(items_.back().data.get());
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
