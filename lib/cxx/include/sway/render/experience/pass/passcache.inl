#include <sway/render/experience/pass/passcache.hpp>

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

template <typename TYPE>
auto PassCache::getOrCreate(const PassDescriptor &desc) -> TYPE * {
  auto hash = core::misc::hashValue(desc);
  auto iter = std::find_if(items_.begin(), items_.end(), [hash](auto &item) { return item.hash == hash; });
  if (iter != items_.end()) {
    return static_cast<TYPE *>(iter->pass.get());
  }

  PassCacheItem item;
  item.hash = hash;
  item.pass = std::make_unique<TYPE>(desc);
  items_.push_back(std::move(item));
  return static_cast<TYPE *>(items_.back().pass.get());
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
