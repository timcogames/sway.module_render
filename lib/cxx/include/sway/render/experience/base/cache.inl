#include <sway/render/experience/base/cache.hpp>
#include <sway/render/experience/pass/passdescriptor.hpp>
#include <sway/render/experience/pipeline/pipelinedescriptor.hpp>

namespace std {
template <>
struct hash<sway::render::experience::PassDescriptor> {
  auto operator()(const sway::render::experience::PassDescriptor &desc) const noexcept -> size_t {
    return desc.hashValue();
  }
};

template <>
struct hash<sway::render::experience::PipelineDescriptor> {
  auto operator()(const sway::render::experience::PipelineDescriptor &desc) const noexcept -> size_t {
    return desc.hashValue();
  }
};
}  // namespace std

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

template <typename TYPE>
Cache<TYPE>::~Cache() {
  for (auto &item : items_) {
    item.data->dispose();
  }

  items_.clear();
}

template <typename TYPE>
template <typename DESC, typename RET>
auto Cache<TYPE>::getOrCreate(const DESC &desc) -> RET * {
  auto hash = core::misc::hashValue(desc);
  auto iter = std::find_if(items_.begin(), items_.end(), [hash](auto &item) { return item.hash == hash; });
  if (iter != items_.end()) {
    return static_cast<RET *>(iter->data.get());
  }

  CacheItem<TYPE> item;
  item.hash = hash;
  item.data = std::make_unique<RET>(desc);
  items_.push_back(std::move(item));
  return static_cast<RET *>(items_.back().data.get());
}

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
