#ifndef SWAY_RENDER_EXPERIENCE_CACHEABLE_HPP
#define SWAY_RENDER_EXPERIENCE_CACHEABLE_HPP

#include <sway/render/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(render)
NS_BEGIN(experience)

class Cacheable {
public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(Cacheable);

#pragma endregion
};

NS_END()  // namespace experience
NS_END()  // namespace render
NS_END()  // namespace sway

#endif  // SWAY_RENDER_EXPERIENCE_CACHEABLE_HPP
