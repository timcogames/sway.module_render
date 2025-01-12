#include <sway/render/experience/utility/cache.hpp>

namespace sway::render {
NS_BEGIN(experience)

Cache::Cache() {}

Cache::~Cache() { items_.clear(); }

NS_END()  // namespace experience
}  // namespace sway::render
