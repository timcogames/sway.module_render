#ifndef SWAY_RENDER_EXPERIENCE_PASSCACHE_HPP
#define SWAY_RENDER_EXPERIENCE_PASSCACHE_HPP

#include <sway/render/experience/pass/_typedefs.hpp>
#include <sway/render/experience/pass/passcacheitem.hpp>
#include <sway/render/experience/pass/passdescriptor.hpp>
#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class PassCache {
public:
#pragma region "Ctors/Dtor"

  PassCache() = default;

  DTOR(PassCache);

#pragma endregion

  template <typename TYPE>
  auto getOrCreate(const PassDescriptor &desc) -> TYPE *;

private:
  PassCacheItemTypedefs::Container_t items_;
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#include <sway/render/experience/pass/passcache.inl>

#endif  // SWAY_RENDER_EXPERIENCE_PASSCACHE_HPP
