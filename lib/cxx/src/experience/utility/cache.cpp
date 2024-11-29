#include <sway/render/experience/utility/cache.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

Cache::Cache() {}

Cache::~Cache() { items_.clear(); }

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway
